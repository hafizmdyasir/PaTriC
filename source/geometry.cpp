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


Vector3D SinGeomtry::getField(Vector3D position, double time) const
{
    switch (variable)
    {
        case 't':
            break;
            
        case 'X':
        case 'x':

            break;
        case 'Y':
        case 'y':

            break;

        case 'Z':
        case 'z':

            break;
        default:
            return Vector3D();
            break;
    }
    return Vector3D();
}



Vector3D GaussGeometry::getField(Vector3D position, double time) const
{
    switch (variable)
    {
        case T:
            break;
            
        case X:

            break;
        case Y:

            break;

        case Z:

            break;
        default:
            return Vector3D();
            break;
    }
    return Vector3D();
}