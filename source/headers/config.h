/*
CONFIG.h
========
Created: 17.04.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Sets up the problem in question.
*/

#ifndef CONFIG_H
#define CONFIG_H


#include <math.h>
#include <vector>
#include <cmath>

#include "pythonserver.h"
#include "magnetic.h"
#include "classes.h"

using namespace std;


extern vector<Vector3D> positions;
extern vector<Vector3D> velocities;
extern vector<Vector3D> efields;
extern vector<Vector3D> bfields;
extern vector<double> gammas;
extern long double currentGamma;

extern Fields fields;
extern Control control;
extern Particles target;
extern Output outputInfo;

extern string execPath;
extern string inputDeckPath;
extern PythonServer pythonServer;

/// @brief Reserve size and resize all vectors to control.numIterations+1
void resizeVectors();


/// @brief Initialize the system.
/// @param _ctrl Control
/// @param _prtcl Particle
/// @param _fields Fields
/// @param _out Output
void initialize(Control _ctrl, Particles _prtcl, Fields _fields, Output _out);


/// @brief Initialize Python server. Call this if you need python server.
void initializeServer();


#endif // CONFIG_H