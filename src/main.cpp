/*
MAIN.cpp
========
Created: 18.04.2024

Copyright
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Main file
*/

#include "build_config.h"
#include "integrator.h"
#include "validation.h"
#include "plotter.h"
#include "patric.h"
#include "misc.h"

#include <filesystem>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <dlfcn.h>
#include <chrono>
#include <omp.h>

// #define MPI_ENABLED true
#if MPI_ENABLED
#include <mpi.h>
int mpi_rank, mpi_size;
int totalNumberOfParticles;
int numberOfParticlesPerProcess;
#endif

using namespace std;

const string libraryFile = "./.input.so";
void* handle;

chrono::milliseconds overallTime;

Integrator chosenIntegrator = Boris;

Control* control;
Fields* fields;
Particle* target;
Output* output;



/// @brief Displays all information provided in the input script and returns true if the user inputs Y or y, implying that the program should proceed with the simulation.
/// @return true if the user wants to proceed, false otherwise.
void displayPrecheckInformation()
{
     std::cout << endl
          << "System Information\n"
          << "\tIntegration algorithm  : " << getIntegratorName(control->integrator) << "\n"
          << "\tTime step              : " << control->dt << "\n"
          << "\tOutput frequency       : " << output->output_f << "\n"
          << "\tNumber of iterations   : " << control->numIterations << "\n"
          << "\tEnd time of simulation : " << control->numIterations*control->dt << "\n";

     if (fields->getElectricField)
          std::cout << endl << "Electric Field applied...";

     if (fields->getMagneticField) 
          std::cout << endl << "Magnetic Field applied...\n";
     

     #if MPI_ENABLED
     for (int rank = 0; rank < mpi_size; rank++)
     {
          int startIndex = rank * numberOfParticlesPerProcess;
          int endIndex = startIndex + numberOfParticlesPerProcess;
          if ((endIndex > totalNumberOfParticles) or (rank == (mpi_size - 1))) endIndex = totalNumberOfParticles;
          std::cout << endl
               << "Rank " << rank << " will handle particles from index " << startIndex << " to " << endIndex-1;
     }
     #else
     std::cout << endl
          << "Target Information\n"
          << "\tCount  : " << target->count << "\n"
          << "\tCharge : " << target->charge << "\n"
          << "\tMass   : " << target->mass << "\n";
     #endif

     std::cout << endl 
          << "Program will use " << omp_get_max_threads() << " thread(s) per rank for parallelization.\n";
}

void performCalculations()
{    
     // This outer loop will not be parallelized. It exists to ensure ease on memory usage
     // The program will save data after every iteration of this loop and clear the memory for the next dump.
     unsigned int numberOfDumps = control->numIterations/output->output_f;
     for (unsigned int dumpNumber = 0; dumpNumber < numberOfDumps; dumpNumber++)
     {
          // Inner loop that should be parallelized. Each iteration is for a single particle.
          // This loop is parallelized using OpenMP. It should NOT output to stdout or stderr or something.
          #pragma omp parallel for
          for (unsigned int particleNumber = 0; particleNumber < target->count; particleNumber++) {
               int bufferSize = output->output_f;
               vector<Momentum> momenta(bufferSize);
               vector<Vector3D> positions(bufferSize);
               vector<Vector3D> eFields(bufferSize);
               vector<Vector3D> mFields(bufferSize);

               real startingGamma = 1 / sqrt(1 - target->velocities[particleNumber].squareAmp() / constants::c2);
               momenta.at(0) = Momentum(target->velocities[particleNumber], startingGamma);
               positions.at(0) = target->positions[particleNumber];

               Vector3D mField(0,0,0);
               Vector3D eField(0,0,0);
               Vector3D x_next_half(0,0,0);

               
               for (unsigned int sim_iter = 0; sim_iter < output->output_f; sim_iter++)
               {
                    unsigned int real_iter = sim_iter + output->output_f*dumpNumber;
                    // Calculate x_n+1/2
                    x_next_half = positions.at(sim_iter) + (momenta.at(sim_iter).momentum() * (control->dt / (2*momenta.at(sim_iter).getGamma())));
                    
                    // Find all fields
                    if (fields->getMagneticField)
                         mField = fields->getMagneticField(x_next_half, real_iter*control->dt);
                    if (fields->getElectricField)
                         eField = fields->getElectricField(x_next_half, real_iter*control->dt);


                    // Store gamma and fields
                    eFields.at(sim_iter) = eField;
                    mFields.at(sim_iter) = mField;

                    if (sim_iter == output->output_f - 1) {
                         // Store the final position and velocity for the next output round.
                         target->velocities[particleNumber] = momenta.back().getV();
                         target->positions[particleNumber] = positions.back();
                    }
                    else {
                         // Update the momentum and position for the next iteration in this round
                         momenta.at(sim_iter+1) = chosenIntegrator(eField, mField, momenta.at(sim_iter).momentum());
                         positions.at(sim_iter+1) = x_next_half + (momenta.at(sim_iter + 1).momentum() * (control->dt / (2*momenta.at(sim_iter + 1).getGamma())));
                    }
               }
               #if MPI_ENABLED
               saveData(positions, momenta, eFields, mFields, *output, mpi_rank*numberOfParticlesPerProcess + particleNumber, dumpNumber);
               #else
               saveData(positions, momenta, eFields, mFields, *output, particleNumber, dumpNumber);
               #endif
          }

          #if MPI_ENABLED
          MPI_Barrier(MPI_COMM_WORLD);
          if (mpi_rank == 0) std::cout << "\n\tDump " << dumpNumber+1 << " of " << numberOfDumps << " completed.";
          #else
          std::cout << "\n\tDump " << dumpNumber+1 << " of " << numberOfDumps << " completed.";
          #endif
     }
}

void cleanupAndExit(int code)
{
     if (output) delete output;
     if (fields) delete fields;
     if (target) delete target;
     if (control) delete control;
     if (handle) dlclose(handle);
     if (filesystem::exists(libraryFile)) filesystem::remove(libraryFile);

     #if MPI_ENABLED
     if (mpi_rank == 0 and filesystem::exists(libraryFile)) filesystem::remove(libraryFile);
     if (code == 0) MPI_Finalize();
     return;

     MPI_Abort(MPI_COMM_WORLD, code);
     
     #else
     exit(code);
     #endif
}

int compileLibrary(string name)
{
     string compile_cmd = string(RUNTIME_CXX) + " -shared -fPIC " + string(RUNTIME_CXXFLAGS) + " " +
          "-w " + "-I" + string(INSTALL_PREFIX) + "/include/patric " + 
          name + " " +
          "-L" + string(INSTALL_PREFIX) + "/lib -lpatriccore " +
          "-o " + libraryFile;

     std::cout << "Compiler   : " << string(RUNTIME_CXX) << "\n\n";

     int compile_result = std::system(compile_cmd.c_str());
     if (compile_result != 0) {
          std::cerr << "Error: Compilation of " << name << " failed.\n";
          return 202;
     }
     return 0;
}

int loadLibrary() {

     handle = dlopen(libraryFile.c_str(), RTLD_LAZY);
     char* dlopen_error = dlerror();
     if (!handle or dlopen_error) {
          std::cerr << "While loading library file, the following error was encountered: \n" << dlopen_error << "\n";
          return 1;
     }

     // Get the configureSimulation function from the library
     ConfigurePatric configure = (ConfigurePatric)dlsym(handle, "configureSimulation");
     const char* dlsym_error = dlerror();
     if (dlsym_error) {
          std::cerr << "Error finding configuration function in input.cpp: \n" << dlsym_error << "\n";
          dlclose(handle);
          return 1;
     }

     #if MPI_ENABLED
     // Call the configure function to set up the simulation parameters. First copy to a temporary Particle for MPI runs.
     Particle* temporaryTarget;
     configure(control, temporaryTarget, fields, output);

     totalNumberOfParticles = temporaryTarget->count;
     numberOfParticlesPerProcess = totalNumberOfParticles / mpi_size;

     // Now, set the target for this process.
     int startIndex = mpi_rank * numberOfParticlesPerProcess;
     int endIndex = startIndex + numberOfParticlesPerProcess;
     if ((endIndex > totalNumberOfParticles) or (mpi_rank == mpi_size - 1)) endIndex = totalNumberOfParticles;
     
     // Create a new Particle object for this process with the subset of particles assigned to it.
     vector<Vector3D> positionsSubset(temporaryTarget->positions.begin() + startIndex, temporaryTarget->positions.begin() + endIndex);
     vector<Vector3D> velocitiesSubset(temporaryTarget->velocities.begin() + startIndex, temporaryTarget->velocities.begin() + endIndex);
     target = new Particle(positionsSubset.size(), temporaryTarget->charge, temporaryTarget->mass,positionsSubset, velocitiesSubset);

     delete temporaryTarget;
     #else

     // Load all particles in the target for non-MPI runs.
     configure(control, target, fields, output);       
     #endif
     return 0;
}

#if MPI_ENABLED
int main(int argc, char **argv)
{
     MPI_Init(&argc, &argv);
     MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
     MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

     if (mpi_rank == 0) {
          printHeader();
          std::cout << "MPI is enabled. Total number of processes: " << mpi_size << "\n";

          if (argc < 2)
          {
               std::cerr << "No configuration file specified. Program will exit." << endl;
               MPI_Abort(MPI_COMM_WORLD, 808);
          }

          string inputScriptPath = argv[1];
          std::cout << "\nInput file : " << inputScriptPath << endl;
          if (!filesystem::exists(inputScriptPath))
          {
               std::cerr << "The provided configuration file does not exist. Program will exit." << endl;
               MPI_Abort(MPI_COMM_WORLD, 404);
          }

          int compilationResult = compileLibrary(inputScriptPath);
          if (compilationResult) cleanupAndExit(compilationResult);
          std::cout << "Simulation configured successfully. \n";
     }
     MPI_Barrier(MPI_COMM_WORLD);

     int loadingResult = loadLibrary();
     if (loadingResult) cleanupAndExit(loadingResult);
     
     if (!validateInitialConditions(control, target, fields, output)) cleanupAndExit(-1);
     MPI_Barrier(MPI_COMM_WORLD);

     if(mpi_rank == 0)
          displayPrecheckInformation();
     
     chrono::system_clock::time_point start, end;
     presetIntegrators(*target, control->dt);
     for (unsigned int i = 0; i < target->count; i++)
          if (setupDiagnostic(*output, mpi_rank*numberOfParticlesPerProcess + i)) cleanupAndExit(-1);
     
          
     if (mpi_rank == 0) start = chrono::system_clock::now();

     switch (control->integrator)
     {
          default:
          case Pusher::Boris:
          chosenIntegrator = Boris;
          break;
          case Pusher::Vay:
          chosenIntegrator = Vay;
          break;
          case Pusher::HigueraCary:
          chosenIntegrator = HigueraCary;    
          break;
     }
          
     MPI_Barrier(MPI_COMM_WORLD);
     
     performCalculations();
     
     MPI_Barrier(MPI_COMM_WORLD);

     if (mpi_rank == 0) {
          end = chrono::system_clock::now();
          overallTime = chrono::duration_cast<chrono::milliseconds>(end-start);
          std::cout << fixed << setprecision(4) << "\n\nTotal time for all particles: " << formatDuration(overallTime) << ".\n"; 
     }
     cleanupAndExit(0);
     return 0;
}

#else
int main(int argc, char **argv)
{
     printHeader();
     
     if (argc < 2)
     {
          std::cerr << "No configuration file specified. Program will exit." << endl;
          return 808;
     }
     
     string inputScriptPath = argv[1];
     std::cout << "\nInput file : " << inputScriptPath << endl;
     if (!filesystem::exists(inputScriptPath))
     {
          std::cerr << "The provided configuration file does not exist. Program will exit." << endl;
          return 404;
     }
     
     int compilationResult = compileLibrary(inputScriptPath);
     if (compilationResult) cleanupAndExit(compilationResult);
     
     
     int loadingResult = loadLibrary();
     if (loadingResult) cleanupAndExit(loadingResult);
     
     
     if (!validateInitialConditions(control, target, fields, output)) cleanupAndExit(-1);
     else cout << "Initial conditions complete and valid... :)\n";
     
     displayPrecheckInformation();
     
     switch (control->integrator)
     {
     default:
     case Pusher::Boris:
          chosenIntegrator = Boris;
          break;
     case Pusher::Vay:
          chosenIntegrator = Vay;
          break;
     case Pusher::HigueraCary:
          chosenIntegrator = HigueraCary;    
          break;
     }
     
     
     presetIntegrators(*target, control->dt);
     
     for (unsigned int i = 0; i < target->count; i++)
     if (setupDiagnostic(*output, i)) cleanupAndExit(-1);
     
     auto start = chrono::system_clock::now();
     
     std::cout << "\n\nMain calculation loop started...";
     performCalculations();
     
     auto end = chrono::system_clock::now();
     overallTime = chrono::duration_cast<chrono::milliseconds>(end-start);
     std::cout << fixed << setprecision(4) << "\n\nTotal time for all particles: " << formatDuration(overallTime) << ".\n"; 
     
     cleanupAndExit(0);
     return 0;
}
#endif
