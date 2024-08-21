/*
GEOMETRY.cpp
============
Created: 24.07.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Definitions for the geometry header
*/

#include "headers/geometry.h"



Vector3D GaussGeometry::getField(Vector3D position, double time) const
{
    long double input;
    switch (variable)
    {
    case 0:
    default:
        input = time;
        break;

    case X:
    case Y:
    case Z:
        input = position[variable];
        break;
    }

    long double magnitude = amp * exp(-pow((input-center)/fwhm, power));
    Vector3D field(0,0,0);
    field[direction] = magnitude;
    return field;
}

Vector3D SinGeometry::getField(Vector3D position, double time) const
{
    long double input;
    switch (variable)
    {
    case 0:
    default:
        input = time;
        break;

    case X:
    case Y:
    case Z:
        input = position[variable];
        break;
    }

    long double magnitude = amplitude * sin(frequency*input + phase);
    Vector3D field(0,0,0);
    field[direction] = magnitude;
    return field;
}