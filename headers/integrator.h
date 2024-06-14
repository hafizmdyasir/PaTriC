/*
INTEGRATOR.h
============
Created: 17.04.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Declare integrators.
*/

#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include <math.h>

#include "classes.h"
#include "misc.h"

using namespace std;


/// @brief Called once at the beginning of the program. The factor q*dt/2m is very commonly used and thus, is saved in the integrator file for faster and cleaner calculation.
/// @param particle The target particle.
/// @param deltaTime The time step.
void presetIntegrators(Particles particle, double deltaTime);


/// @brief Calculate the velocity at the next time instant using Boris method.
/// @param eField Electric field at the mid-position and time.
/// @param magField Magnetic field at the mid-position and time.
/// @param previousU The velocity at this instant. We are talking about u, which includes the relativistic factor.
/// @return The velocity at the next time instant.
Vector3D borisIntegrator(Vector3D eField, Vector3D magField, Vector3D previousV);

/// @brief Calculate the velocity at the next time instant using Vay method.
/// @param eField Electric field at the mid-position and time.
/// @param magField Magnetic field at the mid-position and time.
/// @param previousU The velocity at this instant. We are talking about u, which includes the relativistic factor.
/// @return The velocity at the next time instant.
Vector3D vayIntegrator(Vector3D eField, Vector3D magField, Vector3D previousV);

/// @brief Calculate the velocity at the next time instant using Higuera Cary method.
/// @param eField Electric field at the mid-position and time.
/// @param magField Magnetic field at the mid-position and time.
/// @param previousU The velocity at this instant. We are talking about u, which includes the relativistic factor.
/// @return The velocity at the next time instant.
Vector3D higueraCary(Vector3D eField, Vector3D magField, Vector3D previousV);

#endif // INTEGRATOR_H
