/*
CLASSES.h
=========
Created: 23.04.2025

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Declare all classes that are useful for this program.
*/


#pragma once

#include "vector3d.h"
#include "fields.h"
#include "misc.h"

#include <unordered_map>

using namespace std;


/// @brief Represents the relativistic momentum of the factor
class Momentum
{
private:
    // The velocity vector, without the relativistic factor
    Vector3D velocity;

    // The relativistic factor
    real gamma;

public:
    Momentum() : velocity(Vector3D(0,0,0)), gamma(1.0) {}
    Momentum(Vector3D _vel, real _gm): velocity(_vel), gamma(_gm) {}
    Momentum(real vx, real vy, real vz, real _gm): velocity(Vector3D(vx,vy,vz)), gamma(_gm) {}
    Vector3D momentum() { return velocity*gamma; }
    Vector3D getV() { return velocity; }
    real getGamma() { return gamma; }
};


/// @brief Calculate the velocity at the next time instant with a given method.
/// @param eField Electric field at the mid-position and time.
/// @param magField Magnetic field at the mid-position and time.
/// @param previousU The velocity at this instant. We are talking about u, which includes the relativistic factor.
/// @param currentGamma The relativistic factor associated with the current time step. This will be updated upon integration.
/// @return The velocity at the next time instant.
typedef std::function<Momentum(Vector3D, Vector3D, Vector3D)> Integrator;

/// @brief Simple enum class to identify the integrators. ToDo: Add custom.
enum class Pusher: int {
    Boris = BORIS_INTEGRATOR,
    Vay = VAY_INTEGRATOR,
    HigueraCary = HIGUERA_CARY
};


/// @brief Contains control information about the simulation.
class Control
{
public:
    const real dt;                           // Time step
    const unsigned int numIterations;         // Total number of iterations to run the system for
    
    Pusher integrator;                  // The integrator to use. Must be one of BORIS_INTEGRATOR, VAY_INTEGRATOR, or HIGUERA_CARY, as defined in constants.h.

    Control(): dt(0.0), numIterations(0), integrator(Pusher::Boris) {}

    /// @brief Constructor for the Control class.
    /// @param _dt The time step.
    /// @param _integ The integrator to use. Must be one of BORIS_INTEGRATOR, VAY_INTEGRATOR, or HIGUERA_CARY, as defined in constants.h.
    /// @param _num_iter The number of iterations to run.
    Control(real _dt, unsigned int _num_iter, Pusher _integ)
        : dt(_dt), numIterations(_num_iter), integrator(_integ) {}

};

/// @brief Represents a charged particle that will be used to perform the simulation.
class Particle
{
public:
    const unsigned int count;
    const real charge;
    const real mass;

    vector<Vector3D> positions;
    vector<Vector3D> velocities;

    Particle(): count(0), charge(0.0), mass(0.0), positions(), velocities() {}

    /// @brief Constructor for the Particle class.
    /// @param _count The number of particles.
    /// @param _mass The mass of the particle, in units of electron mass.
    /// @param _charge The charge of the particle, in units of elementary charge.
    /// @param positions The initial positions of the particles.
    /// @param velocities The initial velocities of the particles.
    /// Note: Initial conditions (positions and velocities may be created via helper functions defined in initial_conditions.h)
    Particle(unsigned int _count, real _charge, real _mass, vector<Vector3D> positions, vector<Vector3D> velocities)
        : count(_count), charge(_charge*constants::e), mass(_mass*constants::m_e), positions(positions), velocities(velocities) {}
};


/// @brief Contains information about the external fields to be applied in the simulation.
class Fields
{
public:
    
    FieldGetter getElectricField;
    FieldGetter getMagneticField;
    
    Fields() {}

    /// @brief The constructor for the Fields class.
    /// @param _efield The function that returns the electric field at a given position and time.
    /// @param _mfield The function that returns the magnetic field at a given position and time.
    /// Note: The functions must be of the type FieldGetter, which is defined in fields.h and some helper methods are also present in that file.
    Fields(FieldGetter _efield, FieldGetter _mfield)
        : getElectricField(_efield), getMagneticField(_mfield) {}
};


/// @brief Contains information relevant to the output
class Output
{
public:
    const string fileName;
    const string filePath;

    const unsigned int output_f;              // The data will be written to disk at every output_f-th iteration.

    bool dumpGamma;
    bool dumpEx, dumpEy, dumpEz;
    bool dumpBx, dumpBy, dumpBz;
    bool dumpX, dumpY, dumpZ;
    bool dumpVx, dumpVy, dumpVz;

    Output(): output_f(0), dumpGamma(false), dumpEx(false), dumpEy(false), dumpEz(false), dumpBx(false), dumpBy(false), dumpBz(false), dumpX(false), dumpY(false), dumpZ(false), dumpVx(false), dumpVy(false), dumpVz(false) {}

    /// @brief The constructor for the Output class.
    /// @param _name The name of the output file.
    /// @param _path The path to the output file.
    /// @param _output_f The frequency of output.
    /// @param _vars The variables to be output.
    /// @param _infoDump Whether to dump info.
    Output(string _name, string _path, unsigned int _output_f, vector<string> _vars)
        : fileName(_name), filePath(_path), output_f(_output_f)
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