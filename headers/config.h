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

#include "magnetic.h"
#include "classes.h"

using namespace std;


extern vector<Vector3D> positions;
extern vector<Vector3D> velocities;
extern double currentGamma;

extern Fields fields;
extern Control control;
extern Particles target;
extern Output outputInfo;

// Coil information
extern MagneticCoil coilOne, coilTwo;


void initialize(Control _ctrl, Particles _prtcl, Fields _fields, Output _out);


#endif // CONFIG_H