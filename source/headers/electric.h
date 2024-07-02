/*
ELECTRIC.h
==========
Created: 01.07.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Defines various electric field configurations.
*/

#ifndef ELECTRIC_H
#define ELECTRIC_H


#include <math.h>
#include "geometry.h"


class PointCharge: public Geometry
{
private:
    Vector3D chargeLocation;
    double charge;

public:
    PointCharge() {}
    PointCharge(const Vector3D& pos, double q) : chargeLocation(pos), charge(q) {}

    double getCharge() const { return charge; }
    Vector3D getPosition() const { return chargeLocation; }

    Vector3D getField(Vector3D position, double time) const override;
};


#endif /*ELECTRIC_H*/
