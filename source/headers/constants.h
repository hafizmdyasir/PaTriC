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


using namespace std;

struct constants
{
    // Boltzmann constant
    static constexpr long double k_B = 1.38064852e-23;

    // Speed of light
    static constexpr long double c = 299792458;//137.035999084;

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


// Key for accessing X component of Vector3D object
const int X = 1;
// Key for accessing Y component of Vector3D object
const int Y = 2;
// Key for accessing Z component of Vector3D object
const int Z = 3;


// CONTROL KEYS
const string TIME_STEP = "dt";
const string NUM_ITERS = "num_iters";
const string INTEGRATOR = "integerator";
const string READOUT_FREQ = "readout_freq";

// PARTICLE KEYS
const string MASS = "mass";
const string CHARGE = "charge";
const string PARTICLE_COUNT = "particle_count";
const string INITIAL_POSITION = "initial_position";
const string INITIAL_VELOCITY = "initial_velocity";


// FIELDS KEYS
const string E_FIELD = "e_field";
const string B_FIELD = "b_field";


// OUTPUT KEYS
const string FILENAME = "f_name";
const string FILEPATH = "f_path";
const string FILE_HEADER = "f_header";
const string DUMP_INFO_FILE = 'dump_info_file';
const string DUMP_VARIABLES = "dump_variables";

// DUMP VARIABLES
const string POS_X = "position_x";
const string POS_Y = "position_y";
const string POS_Z = "position_z";

const string VEL_X = "velocity_x";
const string VEL_Y = "velocity_y";
const string VEL_Z = "velocity_z";

const string GAMMA = "gamma";
const string E_FIELD_X = "e_field_x";
const string E_FIELD_Y = "e_field_y";
const string E_FIELD_Z = "e_field_z";
const string B_FIELD_X = "b_field_x";
const string B_FIELD_Y = "b_field_y";
const string B_FIELD_Z = "b_field_z";


#endif // CONSTANTS_H