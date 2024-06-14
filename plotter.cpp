/*
PLOTTER.cpp
===========
Created: 18.05.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Helper functions for plotting
*/

#include "headers/plotter.h"
#include "headers/config.h"
#include "headers/parser.h"
#include "headers/misc.h"



void saveData(vector<Vector3D>& positions, vector<Vector3D>& velocities, Output outInfo, float dt, int count)
{
    
    std::filesystem::create_directories(outputInfo.filePath.c_str());
    ofstream dataFile(outputInfo.filePath + outputInfo.fileName + to_string(count) + ".dat");
    
    // Write variable names at the top.
    dataFile << "# t\t";
    
    if (outputInfo.dumpX)
        dataFile << "x\t";
    if (outputInfo.dumpY)
        dataFile << "y\t";
    if (outputInfo.dumpZ)
        dataFile << "z\t";

    if (outputInfo.dumpVx)
        dataFile << "vx\t";
    if (outputInfo.dumpVy)
        dataFile << "vy\t";
    if (outputInfo.dumpVz)
        dataFile << "vz\t";
    
    dataFile << scientific << setprecision(12) << endl;
    for (int i = 0; i < positions.size(); ++i)
    {
        dataFile << i*control.dt << "\t";
        if (outputInfo.dumpX)
            dataFile << positions[i][X] << "\t";
        if (outputInfo.dumpY)
            dataFile << positions[i][Y] << "\t";
        if (outputInfo.dumpZ)
            dataFile << positions[i][Z] << "\t";

        if (outputInfo.dumpVx)
            dataFile << velocities[i][X] << "\t";
        if (outputInfo.dumpVy)
            dataFile << velocities[i][Y] << "\t";
        if (outputInfo.dumpVz)
            dataFile << velocities[i][Z] << "\t";

        dataFile << endl;
    }
    dataFile.close();
    
}

void saveInfo(Output outputInfo, Control control, Particles particles, float tt)
{
    ofstream infoFile(outputInfo.filePath + outputInfo.fileName + "_info.inf");
    for (int j = 0; j < outputInfo.headers.size(); j++)
        infoFile << "" << outputInfo.headers[j] << endl;

    infoFile << "# tt: " << tt << endl;
    infoFile << "# dt: " << control.dt << endl;
    infoFile << "# ni: " << control.numIterations << endl;

    infoFile << "\nPARTICLES";
    infoFile << endl << "Count   : " << target.count;
    infoFile << endl << "Charge  : " << target.charge;
    infoFile << endl << "Mass    : " << target.mass;
    for (int i = 0; i < target.count; i++)
    {
        infoFile << endl << "\tParticle " << i+1;
        infoFile << endl << "\t\tInitial Position: " << target.initialR(i).to_string();
        infoFile << endl << "\t\tInitial Velocity: " << target.initialV(i).to_string();
    }
}