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

#include "classes.h"
#include "plotter.h"
#include "misc.h"


int setupDiagnostic(Output outputInfo, int particleNumber)
{
    string completeFilePath = outputInfo.filePath + outputInfo.fileName + to_string(particleNumber) + ".dat";
    std::filesystem::create_directories(outputInfo.filePath.c_str());
    ofstream dataFile(completeFilePath, std::ios::trunc);
    if (!dataFile.is_open())
    {
        cerr << "Error: Could not open file " << completeFilePath << " for writing.\n";
        return 1;
    }
    
    // Write variable names at the top.
    dataFile << "# Timestep\t";
    
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

    if (outputInfo.dumpGamma)
        dataFile << "gamma\t";

    if (outputInfo.dumpEx)
        dataFile << "Ex\t";
    if (outputInfo.dumpEy)
        dataFile << "Ey\t";
    if (outputInfo.dumpEz)
        dataFile << "Ez\t";
    
    if (outputInfo.dumpBx)
        dataFile << "Bx\t";    
    if (outputInfo.dumpBy)
        dataFile << "By\t";
    if (outputInfo.dumpBz)
        dataFile << "Bz\t";

    
    dataFile << scientific << setprecision(12) << endl;
    dataFile.close();
    return 0;
}


void saveData(vector<Vector3D>& positions, vector<Momentum>& momenta, vector<Vector3D> eFields, vector<Vector3D> mFields, Output outputInfo, int particleNumber, int dumpNumber)
{
    
    string completeFilePath = outputInfo.filePath + outputInfo.fileName + to_string(particleNumber) + ".dat";
    ofstream dataFile(completeFilePath, std::ios::app);
    
    // Write the dump number etc at the top
    dataFile << "\n# Dump " << dumpNumber;

    
    dataFile << scientific << setprecision(12) << endl;
    for (unsigned int i = 0; i < positions.size(); ++i)
    {
        dataFile << i + outputInfo.output_f * dumpNumber << "\t";
        if (outputInfo.dumpX)
            dataFile << positions[i][X] << "\t";
        if (outputInfo.dumpY)
            dataFile << positions[i][Y] << "\t";
        if (outputInfo.dumpZ)
            dataFile << positions[i][Z] << "\t";

        if (outputInfo.dumpVx)
            dataFile << momenta[i].getV()[X] << "\t";
        if (outputInfo.dumpVy)
            dataFile << momenta[i].getV()[Y] << "\t";
        if (outputInfo.dumpVz)
            dataFile << momenta[i].getV()[Z] << "\t";

        if (outputInfo.dumpGamma)
            dataFile << momenta[i].getGamma() << "\t";
        
        if (outputInfo.dumpEx)
            dataFile << eFields[i][X] << "\t";
        if (outputInfo.dumpEy)
            dataFile << eFields[i][Y] << "\t";
        if (outputInfo.dumpEz)
            dataFile << eFields[i][Z] << "\t";

        if (outputInfo.dumpBx)
            dataFile << mFields[i][X] << "\t";
        if (outputInfo.dumpBy)
            dataFile << mFields[i][Y] << "\t";
        if (outputInfo.dumpBz)
            dataFile << mFields[i][Z] << "\t";        

        dataFile << endl;
    }
    dataFile.close();
    
}