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

#include "headers/initializer.h"
#include "headers/integrator.h"
#include "headers/plotter.h"
#include "headers/config.h"
#include "headers/parser.h"
#include "headers/misc.h"

#include <iostream>
#include <limits.h>
#include <unistd.h>
#include <string.h>
#include <iomanip>
#include <chrono>
#include <math.h>

using namespace std;

string integrator_name;
chrono::milliseconds timeTaken;
chrono::milliseconds overallTime;
auto integrate = borisIntegrator;

bool displayPrecheckInformation()
{
     integrator_name = getIntegratorName(control.integrator);

     switch (control.integrator)
     {
     case 0:
     default:
          integrate = borisIntegrator;
          break;

     case 1:
          integrate = vayIntegrator;
          break;

     case 2:
          integrate = higueraCary;
          break;
     }


     cout << endl
          << "System Information\n"
          << "Number of iterations   : " << control.numIterations << "\n"
          << "Time step in seconds   : " << control.dt << "\n"
          << "End time of simulation : " << control.numIterations*control.dt << "\n";

     cout << endl
          << "Fields Information At Origin and t = 0\n";
     for(auto& efg: fields.eFields)
          cout << efg->getDescription() << "\n";
     for(auto& bfg: fields.bFields)
          cout << bfg->getDescription() << "\n";

     cout << endl
          << "Target Information\n"
          << "Count  :  " << target.count << "\n"
          << "Charge : " << target.charge << "\n"
          << "Mass   :  " << target.mass << "\n";

     for (int i = 0; i < target.count; i++)
     {
          cout << endl << "Particle " << i+1;
          target.initialPositions[i].printVector("\tInitial Position");
          target.initialVelocities[i].printVector("\tInitial Velocity");
     }

     char input;
     cout << endl
          << endl
          << "Continue? (y/n): ";
     cin >> input;
     return (input == 'Y' || input == 'y');
}

void calculationLoop()
{
     cout << "\n\tMain calculation loop started...";
     auto start = chrono::system_clock::now();
     
     for (int i = 0; i < control.numIterations; i++)
     {
          if (control.readout_f > 0)
               if ((i % control.readout_f == 0) || (i+1 == control.numIterations))
                    cout << endl << "\tIteration number " << i;

          // Calculate x_n+1/2
          Vector3D x_next_half = positions.at(i) + (velocities.at(i) * (control.dt / (2 * currentGamma)));
          
          Vector3D mField(0,0,0);
          Vector3D eField(0,0,0);
          Vector3D u_next(0,0,0);

          // Find all fields
          for (int j = 0; j < fields.bFields.size(); j++)
               mField = mField + fields.bFields[j]->getField(x_next_half, i*control.dt);
          for (int j = 0; j < fields.eFields.size(); j++)
               eField = eField + fields.eFields[j]->getField(x_next_half, i*control.dt);

          // Store gamma and fields
          efields.at(i) = eField;
          bfields.at(i) = mField;

          u_next = integrate(eField, mField, velocities.at(i));

          velocities.at(i+1) = u_next;
          gammas.at(i+1) = currentGamma;
          positions.at(i+1) = x_next_half + (velocities.at(i + 1) * (control.dt / (2 * currentGamma)));
     }

     auto end = chrono::system_clock::now();

     timeTaken = chrono::duration_cast<chrono::milliseconds>(end-start);
     overallTime += timeTaken;

     // When loop is finished, the last entry in gammas, efields, and bfields will not have been updated. Set them to nan.
     gammas.at(control.numIterations) = NAN;
     efields.at(control.numIterations) = Vector3D(NAN, NAN, NAN);
     bfields.at(control.numIterations) = Vector3D(NAN, NAN, NAN);
     
     string timeTakenFormatted = formatDuration(timeTaken);
     cout << endl << fixed << setprecision(4)
          << "\tCalculation loop finished in " << timeTakenFormatted << ".\n";
}

void cleanupAndExit(int code)
{
     for (int i = 0; i < fields.bFields.size(); i++)
          delete fields.bFields[i];
     for (int i = 0; i < fields.eFields.size(); i++)
          delete fields.eFields[i];
     
     exit(code);
}

int findPythonScripts(char *deckpath)
{
     char path[PATH_MAX];
     ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
     if (count == -1) {
          perror("readlink");
          return 1;
     }
     path[count] = '\0';

     char *last_slash = strrchr(path, '/');
     if (last_slash != NULL) {
          *last_slash = '\0';
     }

     for(char character: path)
     {
          if (character == '\0') break;
          if (character == ' ') execPath += "\\ ";
          else execPath += character;
     }
     
     return 0;
}

int main(int argc, char **argv)
{
     printHeader();

     if (argc < 2)
     {
          cout << endl
               << endl
               << "No configuration file specified. Program will exit." << endl;
          return 404;
     }

     if (findPythonScripts(argv[1]) != 0)
     {
          cout << endl
               << endl
               << "Error with locating necessary python scripts. Program will exit." << endl;
          return 202;
     }

     inputDeckPath = argv[1];
     cout << "\nInput file: " << inputDeckPath << endl;

     bool parseSuccessful = parseFile(inputDeckPath);
     if (!parseSuccessful || !displayPrecheckInformation())
          cleanupAndExit(-1);

     presetIntegrators(target, control.dt);
     for (int i = 0; i < target.count; i++)
     {
          resizeVectors();

          cout << endl << "Particle number " << i+1;

          currentGamma = 1 / sqrt(1 - target.initialV(i).squareAmp() / constants::c2);
          velocities.at(0) = target.initialV(i)*currentGamma;
          positions.at(0) = target.initialR(i);
          gammas.at(0) = currentGamma;

          calculationLoop();

          cout << "\tSaving particle info...\n";
          saveData(positions, velocities, outputInfo, control.dt, i);
     }

     cout << fixed << setprecision(4) << "\nTotal time for all particles: " << formatDuration(overallTime) << ".\n"; 
     if (outputInfo.dumpInfoFile)
     {
          cout << "Saving program run info..." << endl;
          saveInfo(outputInfo, control, target, overallTime.count());
     }
     cleanupAndExit(0);
     return 0;
}