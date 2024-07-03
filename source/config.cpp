/*
CONFIG.cpp
==========
Created: 17.04.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Setting up the system and target.
*/


#include "headers/config.h"
#include "headers/misc.h"

vector<Vector3D> positions;
vector<Vector3D> velocities;
vector<Vector3D> efields;
vector<Vector3D> bfields;
vector<double> gammas;
double currentGamma;

Fields fields;
Control control;
Particles target;
Output outputInfo;

PythonServer pythonServer;
string inputDeckPath;
bool serverInitialized = false;

void resizeVectors()
{
    // Clear all vectors
    positions.clear();
    velocities.clear();
    efields.clear();
    bfields.clear();
    gammas.clear();

    positions.reserve(control.numIterations + 1);
    positions.resize(control.numIterations + 1);
    
    velocities.reserve(control.numIterations + 1);
    velocities.resize(control.numIterations + 1);

    efields.reserve(control.numIterations + 1);
    efields.resize(control.numIterations + 1);

    bfields.reserve(control.numIterations + 1);
    bfields.resize(control.numIterations + 1);

    gammas.reserve(control.numIterations + 1);
    gammas.resize(control.numIterations + 1);
}


void initialize(Control _ctrl, Particles _prtcl, Fields _fields, Output _out)
{
    control = _ctrl;
    target = _prtcl;
    fields = _fields;
    outputInfo = _out;
    resizeVectors();
}

void initializeServer()
{
    if (!serverInitialized)
    {
        serverInitialized = true;
        pythonServer.startServer(inputDeckPath);
    }
}


// Owing to something necessary, this is being defined here.
CustomGeometry::CustomGeometry(const string& _fName): functionName(_fName)
{
    initializeServer();
}

Vector3D CustomGeometry::getField(Vector3D position, double time) const
{
    Vector3D result;
    pythonServer.callFunction(functionName, position, time, result);
    return result;
}

