/*
CONFIG.cpp
==========
Created: 17.04.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Setting up the system and target.
*/


#include "headers/config.h"
#include "headers/misc.h"


// BOTTLE CONFIGURATIONS
float current = 1e4;
float bottleLength = 0.5;
float bottleRadius = 5e-2;

MagneticCoil coilOne(bottleRadius, current, bottleLength/2);
MagneticCoil coilTwo(bottleRadius, current, -bottleLength/2);



/* /// @brief Calculates the field due to a current coil located with its axis along z-direction.
/// @param r_cartesian The cartesian position of the point at which, field is to be calculated.
/// @param z_coil The coil is located in the z = z_coil plane.
/// @return The magnetic field B due to the coil.
Vector3D offAxisField(Vector3D r_cartesian, double z_coil)
{
    // r, phi, z of polar coordinates.
    long double r = sqrt(pow(r_cartesian[1], 2) + pow(r_cartesian[2], 2));
    long double phi = atan2(r_cartesian[2], r_cartesian[1]);
    long double z = r_cartesian[3];

    long double k_c_denom = sqrt(pow(r + bottleRadius, 2) + pow(z - z_coil, 2));
    long double k_c = sqrt(4*bottleRadius*r) / k_c_denom;

    // Elliptic integrals
    long double K_kc = ellint_1(k_c, M_PI_2);
    long double E_kc = ellint_2(k_c, M_PI_2);
    
    long double commonOuter = (constants::mu_0 * current) / (2*k_c_denom*M_PI);
    long double commonInner = E_kc / (pow(r - bottleRadius, 2) + pow(z - z_coil, 2));

    long double B_r = (commonOuter * (z - z_coil) / r) * (-K_kc + commonInner * (r*r + bottleRadius*bottleRadius + pow(z-z_coil, 2)));
    long double B_z = commonOuter * (K_kc - commonInner * (r*r - bottleRadius*bottleRadius + pow(z - z_coil, 2)));


    return Vector3D(B_r * cos(phi), B_r * sin(phi), B_z);
}
 */


Vector3D magFieldAt(Vector3D position, double time)
{
    return (coilOne.getField(position, 0) + coilTwo.getField(position, 0));
}



vector<Vector3D> positions;
vector<Vector3D> velocities;
double currentGamma;

Fields fields;
Control control;
Particles target;
Output outputInfo;

/// @brief Initialize the system.
/// @param control Control
/// @param particle Particle
/// @param output Output
void initialize(Control _ctrl, Particles _prtcl, Fields _fields, Output _out)
{
    control = _ctrl;
    target = _prtcl;
    fields = _fields;
    outputInfo = _out;

    positions.reserve(control.numIterations+1);
    velocities.reserve(control.numIterations+1);
    positions.resize(control.numIterations + 1);
    velocities.resize(control.numIterations + 1);
}



