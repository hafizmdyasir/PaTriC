/*
INITIAL CONDITION.h
===================
Created: 12.10.2026

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Declares helper functions to set up particle initial conditions.
*/

#pragma once

#include <functional>
#include <random>
#include <omp.h>

#include "vector3d.h"


std::vector<Vector3D> getSameIC(int count, Vector3D value);
std::vector<Vector3D> getMaxwellianIC(int count, real temperature, real mass);
std::vector<Vector3D> getRandomIC(int count, real xmin, real xmax, real ymin, real ymax, real zmin, real zmax);
std::vector<Vector3D> getRegularIC(int count, real xmin, real xmax, real ymin, real ymax, real zmin, real zmax);

