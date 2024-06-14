/*
INITIALIZER.h
=============
Created: 04.06.2024

Copyright
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Used to initialize particles' positions and velocities in different forms.
*/


#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <vector>
#include <random>
#include <cmath>


#include "vector3d.h"

using namespace std;


/// @brief Generate a vector of numPoints Vector3D objects representing particle positions. These are spread uniformly in the range of rMinimum to rMaximum, both exclusive.
/// @param rMinimum The minimum position
/// @param rMaximum The maximum position
/// @param numPoints The number of particles
/// @return A vector of numPoints Vector3D objects, each for each particle.
vector<Vector3D> getUniformPositions(Vector3D rMinimum, Vector3D rMaximum, int numPoints);


/// @brief Generate a vector of numPoints Vector3D objects representing particle velocities. These are spread uniformly in the range of rMinimum to rMaximum, both exclusive.
/// @param rMinimum The minimum position
/// @param rMaximum The maximum position
/// @param numPoints The number of particles
/// @return A vector of numPoints Vector3D objects, each for each particle.
vector<Vector3D> getUniformVelocities(Vector3D vMinimum, Vector3D vMaximum, int numPoints);



/// @brief Generate randomly distributed positions for the positions. These are drawn from a uniform distribution between 0 and 1 and then normalized.
/// @param rMinimum The minimum position.
/// @param rMaximum The maximum position.
/// @param numPoints The number of particles.
/// @return A vector of random positions
vector<Vector3D> getRandomPositions(Vector3D rMinimum, Vector3D rMaximum, int numPoints);


/// @brief Generate randomly distributed velocities for the particles. These are drawn from a Maxwellian distribution at temperature given by temperature
/// @param temperature The temperature of the Maxwellian distribution
/// @param mass The mass of the target species
/// @param numPoints The number of particles
/// @return A vector of random velocities
vector<Vector3D> getRandomVelocities(double temperature, double mass, int numPoints);


#endif // INITIALIZER_H