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
#include <iomanip>
#include <chrono>
#include <math.h>

using namespace std;

string integrator_name;
double timeTaken = 0.0;
double overallTime = 0.0;
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
          << endl
          << "Running the program for " << control.numIterations
          << " steps with time interval " << control.dt << " using " << integrator_name << " integrator";

     cout << endl
          << endl
          << "Fields configuration is:";

     for (auto& efg: fields.eFields)
          cout << endl << (efg->getField(Vector3D(), 0)).to_string();
     for (auto& bfg: fields.bFields)
          cout << endl << (bfg->getField(Vector3D(), 0)).to_string();

     cout << endl
          << endl
          << "Target configuration is:";

     cout << endl << "Count   : " << target.count;
     cout << endl << "Charge  : " << target.charge;
     cout << endl << "Mass    : " << target.mass;
     for (int i = 0; i < target.count; i++)
     {
          cout << endl << "Particle " << i+1;
          target.initialPositions[i].printVector("Initial Position");
          target.initialVelocities[i].printVector("Initial Velocity");
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
          gammas.at(i) = currentGamma;
          efields.at(i) = eField;
          bfields.at(i) = mField;

          u_next = integrate(eField, mField, velocities.at(i));
          velocities.at(i+1) = u_next;
          positions.at(i+1) = x_next_half + (velocities.at(i + 1) * (control.dt / (2 * currentGamma)));
     }

     auto end = chrono::system_clock::now();
     chrono::duration<double> elapsed = end - start;
     timeTaken = elapsed.count();
     overallTime += timeTaken;

     // When loop is finished, the last entry in gammas, efields, and bfields will not have been updated. Set them to nan.
     gammas.at(control.numIterations) = NAN;
     efields.at(control.numIterations) = Vector3D(NAN, NAN, NAN);
     bfields.at(control.numIterations) = Vector3D(NAN, NAN, NAN);

     cout << endl << fixed << setprecision(4)
          << "\tCalculation loop finished in " << timeTaken << " seconds.\n";
}

void cleanupAndExit(int code)
{
     for (int i = 0; i < fields.bFields.size(); i++)
          delete fields.bFields[i];
     for (int i = 0; i < fields.eFields.size(); i++)
          delete fields.eFields[i];
     
     exit(code);
}

int main(int argc, char **argv)
{
     printHeader();

     if (argc < 2)
     {
          cout << endl
               << endl
               << "No configuration file specified. Program will exit.";
          return 404;
     }

     string configFile = argv[1];
     cout << endl
          << "Loading configuration file located at " << configFile;
     bool parseSuccessful = parseFile(configFile);
     if (!parseSuccessful)
          cleanupAndExit(-1);

     presetIntegrators(target, control.dt);
     if (!displayPrecheckInformation())
          cleanupAndExit(-1);

     for (int i = 0; i < target.count; i++)
     {
          resizeVectors();

          cout << endl << "Particle number " << i+1;

          currentGamma = 1 / sqrt(1 - target.initialV(i).squareAmp() / constants::c2);
          velocities.at(0) = target.initialV(i)*currentGamma;
          positions.at(0) = target.initialR(i);

          calculationLoop();

          cout << "\tSaving particle info...\n";
          saveData(positions, velocities, outputInfo, control.dt, i);
     }

     cout << fixed << setprecision(4) << "\nTotal time for all particles: " << overallTime << " seconds.\n" 
          << "Saving program run info..."
          << endl;
     
     saveInfo(outputInfo, control, target, overallTime);
     cleanupAndExit(0);
     return 0;
}