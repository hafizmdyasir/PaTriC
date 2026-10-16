/*
INTEGRATOR.h
============
Created: 23.04.2025

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Declare integrators.
*/

#pragma once

#include <math.h>
#include <functional>

#include "classes.h"

using namespace std;


/// @brief Called once at the beginning of the program. The factor q*dt/2m is very commonly used and thus, is saved in the integrator file for faster and cleaner calculation.
/// @param Particle The target particle
/// @param deltaTime The time step to be used for integration.
void presetIntegrators(Particle particle, real deltaTime);

/// @brief Returns the name of the integrator as a string.
/// @param integrator The integrator to get the name of.
/// @return The name of the integrator as a string.
string getIntegratorName(Pusher integrator);

extern Integrator Boris;
extern Integrator Vay;
extern Integrator HigueraCary;