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
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <iomanip>
#include <cstdlib>
#include <dlfcn.h>
#include <math.h>
#include <chrono>
#include <omp.h>

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
bool displayPrecheckInformation()
{
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
     

     std::cout << endl
          << "Target Information\n"
          << "\tCount  : " << target->count << "\n"
          << "\tCharge : " << target->charge << "\n"
          << "\tMass   : " << target->mass << "\n";

     std::cout << endl 
          << "\nProgram will use " << omp_get_max_threads() << " thread(s) for parallelization of "
          << target->count << " particles.\n";

     char input;
     std::cout << endl
          << endl
          << "Continue? (y/n): ";
     cin >> input;
     return (input == 'Y' || input == 'y');
}

void performCalculations()
{
     std::cout << "\n\nMain calculation loop started...";
     auto start = chrono::system_clock::now();

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
               
               saveData(positions, momenta, eFields, mFields, *output, particleNumber, dumpNumber);
          }

          std::cout << "\n\tDump " << dumpNumber+1 << " of " << numberOfDumps << " completed.";
     }

     auto end = chrono::system_clock::now();

     overallTime = chrono::duration_cast<chrono::milliseconds>(end-start);
}

void cleanupAndExit(int code)
{
     if (output) delete output;
     if (fields) delete fields;
     if (target) delete target;
     if (control) delete control;
     if (handle) dlclose(handle);
     if (filesystem::exists(libraryFile)) filesystem::remove(libraryFile);
     exit(code);
}

int compileInput(string name)
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

int loadLibraryFile() {

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

     // Call the configure function to set up the simulation parameters
     configure(control, target, fields, output);

     std::cout << "Simulation configured successfully. \n";
     return 0;
}

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

     int compilationResult = compileInput(inputScriptPath);
     if (compilationResult) cleanupAndExit(compilationResult);
    

     int loadingResult = loadLibraryFile();
     if (loadingResult) cleanupAndExit(loadingResult);


     if (!validateInitialConditions(control, target, fields, output)) cleanupAndExit(-1);
     else cout << "Initial conditions complete and valid... :)\n";
     if (!displayPrecheckInformation()) cleanupAndExit(-1);

     presetIntegrators(*target, control->dt);

     for (unsigned int i = 0; i < target->count; i++)
          if (setupDiagnostic(*output, i)) cleanupAndExit(-1);
     
     performCalculations();

     std::cout << fixed << setprecision(4) << "\n\nTotal time for all particles: " << formatDuration(overallTime) << ".\n"; 
          
     cleanupAndExit(0);
     return 0;
}
