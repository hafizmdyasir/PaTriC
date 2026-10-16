/*
FIELDS.h
========
Created: 07.10.2026

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Declares function that can be used to calculate fields.
*/

#pragma once

#include "vector3d.h"
#include "misc.h"
#include <functional>

typedef std::function<Vector3D(Vector3D, real)> FieldGetter;


FieldGetter getConstantField(Vector3D components);
FieldGetter getSineField(real amplitude, real frequency, real phase, int variable, Vector3D direction);
FieldGetter getGaussianField(real amplitude, real sigma, real center, float power, int variable, Vector3D direction);



