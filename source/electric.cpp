/*
ELECTRIC.cpp
============
Created: 01.07.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Defines various electric field configurations.
*/


#include "headers/electric.h"


using namespace std;


Vector3D PointCharge::getField(Vector3D position, double time) const
{
    Vector3D r = position - chargeLocation;
    Vector3D e = r * (constants::k * charge / pow(r.amplitude(), 3));
    return e;
}