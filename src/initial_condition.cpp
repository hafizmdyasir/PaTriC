/*
INITIAL CONDITION.cpp
=====================
Created: 12.10.2026

Copyright 
Mohammad Yasir
Indian Institute of Technology, Delhi

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Declares helper functions to set up particle initial conditions.
*/


#include "initial_condition.h"

/// @brief Get the same initial condition for all particles.
/// @param count The number of particles.
/// @param value The value to be assigned to all particles.
/// @return The vector of initial conditions.
std::vector<Vector3D> getSameIC(int count, Vector3D value)
{
    std::vector<Vector3D> positions(count, value);
    return positions;
}

/// @brief Get random initial conditions for the particles.
/// @param xmin The minimum value for the x-coordinate.
/// @param xmax The maximum value for the x-coordinate.
/// @param ymin The minimum value for the y-coordinate.
/// @param ymax The maximum value for the y-coordinate.
/// @param zmin The minimum value for the z-coordinate.
/// @param zmax The maximum value for the z-coordinate.
/// @return The vector of initial conditions.
std::vector<Vector3D> getRandomIC(int count, real xmin, real xmax, real ymin, real ymax, real zmin, real zmax)
{
    std::vector<Vector3D> values(count, Vector3D(NAN, NAN, NAN));

    std::random_device rd;
    std::mt19937 gen(rd());

    #pragma omp parallel for
    for (int i = 0; i < count; ++i)
    {
        real x = (xmin == xmax) ? xmin : std::uniform_real_distribution<real>(xmin, xmax)(gen);
        real y = (ymin == ymax) ? ymin : std::uniform_real_distribution<real>(ymin, ymax)(gen);
        real z = (zmin == zmax) ? zmin : std::uniform_real_distribution<real>(zmin, zmax)(gen);
        values.at(i) = Vector3D(x, y, z);
    }
    return values;
}

/// @brief Get regular initial conditions for the particles.
/// @param count The number of particles.
/// @param xmin The minimum value for the x-coordinate.
/// @param xmax The maximum value for the x-coordinate.
/// @param ymin The minimum value for the y-coordinate.
/// @param ymax The maximum value for the y-coordinate.
/// @param zmin The minimum value for the z-coordinate.
/// @param zmax The maximum value for the z-coordinate.
/// @return The vector of initial conditions.
std::vector<Vector3D> getRegularIC(int count, real xmin, real xmax, real ymin, real ymax, real zmin, real zmax)
{
    std::vector<Vector3D> values(count, Vector3D(NAN, NAN, NAN));
    real spacing_x = (xmax - xmin) / std::cbrt(count);
    real spacing_y = (ymax - ymin) / std::cbrt(count);
    real spacing_z = (zmax - zmin) / std::cbrt(count);

    int numX = static_cast<int>((xmax - xmin) / spacing_x);
    int numY = static_cast<int>((ymax - ymin) / spacing_y);
    int numZ = static_cast<int>((zmax - zmin) / spacing_z);

    #pragma omp parallel for
    for (int i = 0; i < count; ++i)
    {
        int ix = i % numX;
        int iy = (i / numX) % numY;
        int iz = (i / (numX * numY)) % numZ;

        real x = xmin + ix * spacing_x;
        real y = ymin + iy * spacing_y;
        real z = zmin + iz * spacing_z;

        values.at(i) = Vector3D(x, y, z);
    }
    return values;
}


/// @brief Generate a Maxwellian distribution of values.
/// @param temperature The temperature of the system.
/// @param mass The mass of the particles.
/// @param count The number of values to generate.
/// @return A vector of Maxwellian-distributed values.
vector<real> generateMaxwellian(real temperature, real mass, int count)
{
    vector<real> result;
    result.resize(count);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    
    real sigma = sqrt(constants::k_B*temperature/mass);

    #pragma omp parallel for
    for (int i = 0; i < count; ++i) {
        // Generate Gaussian-distributed numbers using Box-Muller transform
        real u1 = dis(gen);
        real u2 = dis(gen);
        real z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);

        // Transform to Maxwellian distribution
        real v = sigma * fabs(z0);
        result[i] = v;
    }
    return result;
}


/// @brief Get Maxwellian initial conditions for the particles.
/// @param count The number of particles.
/// @param temperature The temperature of the system.
/// @param mass The mass of the particles.
/// @return The vector of initial conditions.
std::vector<Vector3D> getMaxwellianIC(int count, real temperature, real mass)
{
    std::vector<Vector3D> values(count, Vector3D(NAN, NAN, NAN));

    vector<double> vx = generateMaxwellian(temperature, mass, count);
    vector<double> vy = generateMaxwellian(temperature, mass, count);
    vector<double> vz = generateMaxwellian(temperature, mass, count);
    
    #pragma omp parallel for
    for (int i = 0; i < count; i++)
        values.at(i) = Vector3D(vx[i], vy[i], vz[i]);
    
    return values;
}