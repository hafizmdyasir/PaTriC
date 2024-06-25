/*
GEOMETRY.h
==========
Created: 06.06.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Contains a geometry class that can be overriden.
*/


#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "vector3d.h"




/// @brief Virtual class that will be overriden by all field geometries.
class Geometry
{
public:
    virtual ~Geometry() = default;
    virtual Vector3D getField(Vector3D position, double time) const = 0;
};


/// @brief The StaticGeomtry class gives rise to a constant electric/magnetic field.
class StaticGeometry : public Geometry
{
private:
    long double x, y, z;
public:
    StaticGeometry(long double x, long double y, long double z)
        : x(x), y(y), z(z) {}

    Vector3D getField(Vector3D position, double time) const 
    {
        return Vector3D(x, y, z);
    }
};




#endif // GEOMETRY_H
