/*
CONSTANTS.h
===========
Created: 23.04.2025

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Contains only constants
*/


#pragma once

#include <string>
#include <math.h>
#include <array>

#define T 5    // Key that represents time.
#define X 0    // Key for accessing X component of Vector3D object
#define Y 1    // Key for accessing Y component of Vector3D object
#define Z 2    // Key for accessing Z component of Vector3D object

#if defined(HIGH_PRECISION)
#define real long double
#elif defined(LOW_PRECISION)
#define real float
#else
#define real double
#endif

#define BORIS_INTEGRATOR 0
#define VAY_INTEGRATOR 1
#define HIGUERA_CARY 2
constexpr std::array<std::string_view, 3> INTEGRATORS = {
    "Boris",
    "Vay",
    "Higuera-Cary"
};

// DUMP VARIABLES
#define POS_X "position_x"
#define POS_Y "position_y"
#define POS_Z "position_z"

#define VEL_X "velocity_x"
#define VEL_Y "velocity_y"
#define VEL_Z "velocity_z"

#define GAMMA "gamma"
#define E_FIELD_X "e_field_x"
#define E_FIELD_Y "e_field_y"
#define E_FIELD_Z "e_field_z"
#define B_FIELD_X "b_field_x"
#define B_FIELD_Y "b_field_y"
#define B_FIELD_Z "b_field_z"

using namespace std;

#ifdef USE_SI_UNITS
struct constants
{
    // Boltzmann constant
    static constexpr real k_B = 1.38064852e-23;

    // Speed of light
    static constexpr real c = 299792458;

    // Speed of light squared
    static constexpr real c2 = c*c;
    
    // Permittivity of free space.
    static constexpr real mu_0 = 4*M_PI*1e-7;

    // Mass of electron.
    static constexpr real m_e = 9.1093837139e-31;

    // Elementary charge.
    static constexpr real e = 1.602176634e-19;

    // Permittivity of vacuum
    static constexpr real epsilon_0 = 8.854187817e-12;

    // Force constant for Coulomb force
    static constexpr real k = 8.987551787368e9;
};
#else
struct constants
{
    // Boltzmann constant
    static constexpr real k_B = 1;

    // Speed of light
    static constexpr real c = 1;

    // Speed of light squared
    static constexpr real c2 = c*c;
    
    // Permittivity of free space.
    static constexpr real mu_0 = 1;

    // Mass of electron.
    static constexpr real m_e = 1;

    // Elementary charge.
    static constexpr real e = 1;

    // Permittivity of vacuum
    static constexpr real epsilon_0 = 1;

    // Force constant for Coulomb force
    static constexpr real k = 1;
};
#endif