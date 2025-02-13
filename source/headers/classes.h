/*
CLASSES.h
=========
Created: 21.02.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Holds data classes and structures.
*/

#ifndef CLASSES_H
#define CLASSES_H


#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <memory>

#include "initializer.h"
#include "constants.h"
#include "geometry.h"
#include "vector3d.h"
#include "misc.h"

using namespace std;


/// @brief Contains control information about the simulation.
class Control
{
public:
    float dt;
    unsigned int integrator;
    unsigned int numIterations;
    unsigned int readout_f;

    Control() {}
    Control(float _dt, unsigned int _integ, unsigned int _num_iter, unsigned int _readout)
        : dt(_dt), integrator(_integ), numIterations(_num_iter), readout_f(_readout) {}

};


/// @brief Represents the set of charged particles that will be used to perform the simulation.
class Particles
{
public:
    float mass;
    float charge;
    unsigned int count;

    vector<Vector3D> initialPositions;
    vector<Vector3D> initialVelocities;

    Particles() {}
    Particles(float _mass, float _charge, int _count, vector<Vector3D> _posInit, vector<Vector3D> _velInit)
        : mass(_mass*constants::m_e), charge(_charge*constants::e), count(_count), initialPositions(_posInit), initialVelocities(_velInit) {}

    Vector3D initialR(int i) { return initialPositions[i]; }
    Vector3D initialV(int i) { return initialVelocities[i]; }
};



class Fields
{
public:

    // Static Components
    // vector<StaticGeometry> staticB;
    // vector<StaticGeometry> staticE;

    // vector<MagneticWire> wireB;
    // vector<MagneticCoil> coilB;


    vector<Geometry*> eFields;
    vector<Geometry*> bFields;

    Fields() {}
    Fields(vector<Geometry*> _e, vector<Geometry*> _b)
        : eFields(_e), bFields(_b) {}
};


/// @brief Contains information relevant to the output
class Output
{
public:
    string fileName;
    string filePath;
    bool dumpInfoFile;
    vector<string> headers;

    bool dumpGamma;
    bool dumpEx, dumpEy, dumpEz;
    bool dumpBx, dumpBy, dumpBz;
    bool dumpX, dumpY, dumpZ;
    bool dumpVx, dumpVy, dumpVz;

    Output() {}
    Output(string _name, string _path, vector<string> _subs, bool _infoDump, vector<string> _vars)
        : fileName(_name), filePath(_path), dumpInfoFile(_infoDump), headers(_subs)
        {
            dumpX = contains(_vars, POS_X);
            dumpY = contains(_vars, POS_Y);
            dumpZ = contains(_vars, POS_Z);
            dumpVx = contains(_vars, VEL_X);
            dumpVy = contains(_vars, VEL_Y);
            dumpVz = contains(_vars, VEL_Z);
            dumpEx = contains(_vars, E_FIELD_X);
            dumpEy = contains(_vars, E_FIELD_Y);
            dumpEz = contains(_vars, E_FIELD_Z);
            dumpBx = contains(_vars, B_FIELD_X);
            dumpBy = contains(_vars, B_FIELD_Y);
            dumpBz = contains(_vars, B_FIELD_Z);
            dumpGamma = contains(_vars, GAMMA);
        }
};


#endif