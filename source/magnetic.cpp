/*
MAGNETIC.cpp
============
Created: 03.06.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Defines various magnetic field configurations.
*/


#include "headers/magnetic.h"




Vector3D onAxisField(Vector3D r_cartesian, double z_coil, double radius, double current)
{
    long double distance = r_cartesian[Z];
    long double magnitude = constants::mu_0 * current * radius * radius / (2 * pow(radius*radius + pow(distance-z_coil, 2), 3/2));
    return Vector3D(0, 0, magnitude);
}

Vector3D offAxisField(Vector3D r_cartesian, double z_coil, double radius, double current)
{
    // r, phi, z of polar coordinates.
    long double r = sqrt(pow(r_cartesian[1], 2) + pow(r_cartesian[2], 2));
    long double phi = atan2(r_cartesian[2], r_cartesian[1]);
    long double z = r_cartesian[3];

    long double k_c_denom = sqrt(pow(r + radius, 2) + pow(z - z_coil, 2));
    long double k_c = sqrt(4*radius*r) / k_c_denom;

    // Elliptic integrals
    long double K_kc = ellint_1(k_c, M_PI_2);
    long double E_kc = ellint_2(k_c, M_PI_2);
    
    long double commonOuter = (constants::mu_0 * current) / (2*k_c_denom*M_PI);
    long double commonInner = E_kc / (pow(r - radius, 2) + pow(z - z_coil, 2));

    long double B_r = (commonOuter * (z - z_coil) / r) * (-K_kc + commonInner * (r*r + radius*radius + pow(z-z_coil, 2)));
    long double B_z = commonOuter * (K_kc - commonInner * (r*r - radius*radius + pow(z - z_coil, 2)));


    return Vector3D(B_r * cos(phi), B_r * sin(phi), B_z);
}


Vector3D MagneticCoil::getField(Vector3D position, double time) const
{
    if (position[X] == 0 && position[Y] == 0)
        return onAxisField(position, this->zPosition, this->radius, this->current);
    else 
        return offAxisField(position, this->zPosition, this->radius, this->current);
}

string MagneticCoil::getDescription() const
{
    return "Magnetic Coil";
}