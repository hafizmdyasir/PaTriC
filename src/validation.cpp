/*
VALIDATION.cpp
==============
Created: 12.10.2026

Copyright 
Mohammad Yasir
Indian Institute of Technology, Delhi

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Declares helper functions to confirm initial conditions are valid.
*/

#include "classes.h"

bool validateInitialConditions(Control* control, Particle* target, Fields* fields, Output* output)
{
    // Validate control.
    if (control->dt <= 0.0) {
        std::cerr << "Error: Time step (dt) must be positive.\n";
        return false;
    }

    if (control->numIterations <= 0) {
        std::cerr << "Error: Number of iterations must be positive.\n";
        return false;
    }

    // Validate particles.
    if (target->count <= 0) {
        std::cerr << "Error: Number of particles must be positive.\n";
        return false;
    }

    if (target->mass <= 0.0) {
        std::cerr << "Error: Particle mass must be positive.\n";
        return false;
    }

    if (target->charge == 0.0) {
        std::cerr << "Error: Particle charge cannot be zero.\n";
        return false;
    }

    return true;
}