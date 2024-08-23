/*
CONSTANTS.h
===========
Created: 04.06.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Contains only constants
*/


#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
#include <math.h>

#define T 0    // Key that represents time.
#define X 1    // Key for accessing X component of Vector3D object
#define Y 2    // Key for accessing Y component of Vector3D object
#define Z 3    // Key for accessing Z component of Vector3D object

// CONTROL KEYS
#define TIME_STEP "dt"
#define NUM_ITERS "num_iters"
#define INTEGRATOR "integerator"
#define READOUT_FREQ "readout_freq"

// PARTICLE KEYS
#define MASS "mass"
#define CHARGE "charge"
#define PARTICLE_COUNT "particle_count"
#define INITIAL_POSITION "initial_position"
#define INITIAL_VELOCITY "initial_velocity"

// FIELDS KEYS
#define E_FIELD "e_field"
#define B_FIELD "b_field"

// OUTPUT KEYS
#define FILENAME "f_name"
#define FILEPATH "f_path"
#define FILE_HEADER "f_header"
#define DUMP_INFO_FILE "dump_info_file"
#define DUMP_VARIABLES "dump_variables"

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

struct constants
{
    // Boltzmann constant
    static constexpr long double k_B = 1.38064852e-23;

    // Speed of light
    static constexpr long double c = 299792458;

    // Speed of light squared
    static constexpr long double c2 = c*c;
    
    // Permittivity of free space.
    static constexpr long double mu_0 = 4*M_PI*1e-7;

    // Mass of electron.
    static constexpr long double m_e = 9.1093837139e-31;

    // Elementary charge.
    static constexpr long double e = 1.602176634e-19;

    // Permittivity of vacuum
    static constexpr long double epsilon_0 = 8.854187817e-12;

    // Force constant for Coulomb force
    static constexpr long double k = 8.987551787368e9;
};


#endif // CONSTANTS_H