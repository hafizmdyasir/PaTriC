/*
MAGNETIC.h
==========
Created: 03.06.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Defines various magnetic field configurations.
*/

#ifndef MAGNETIC_H
#define MAGNETIC_H


#include "geometry.h"
#include "classes.h"



class MagneticWire: public Geometry
{
private:
    double current;
    double length;
    int direction;

    Vector3D midpoint;

public:
    MagneticWire() {}
    MagneticWire(double _cur, double _len, Vector3D _mid, int _dir)
        : current(_cur), length(_len), midpoint(_mid), direction(_dir) {}

    double getLength() const { return length; }
    double getCurrent() const { return current; }
    int getDirection() const { return direction; }
    Vector3D getMidpoint() const { return midpoint; }
    
    Vector3D getField(Vector3D position, double time) const override;
};


class MagneticCoil: public Geometry
{
private:
    double radius;
    double current;
    double zPosition;

public:
    MagneticCoil(): current(0.0), radius(0.0), zPosition(0.0) {}
    MagneticCoil(double _r, double _i, double _z): current(_i), radius(_r), zPosition(_z) {}

    double getCoilZPosition() const { return zPosition; }
    double getCoilCurrent() const { return current; }
    double getCoilRadius() const { return radius; }

    Vector3D getField(Vector3D position, double time) const override;

};







#endif // MAGNETIC_H