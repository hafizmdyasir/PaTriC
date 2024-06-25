/*
INITIALIZER.cpp
===============
Created: 04.06.2024

Copyright
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Used to initialize particles' positions and velocities in different forms.
*/



#include "headers/initializer.h"

vector<double> generateMaxwellian(double T, double m, int n)
{
    vector<double> result;
    result.resize(n);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    
    double sigma = sqrt(constants::k*T/m);

    for (int i = 0; i < n; ++i) {
        // Generate Gaussian-distributed numbers using Box-Muller transform
        double u1 = dis(gen);
        double u2 = dis(gen);
        double z0 = sqrt(-2.0 * log(u1)) * cos(2.0 * M_PI * u2);
        double z1 = sqrt(-2.0 * log(u1)) * sin(2.0 * M_PI * u2);

        // Transform to Maxwellian distribution
        double v = sigma * fabs(z0);
        result[i] = v;
    }
    return result;
}


vector<Vector3D> getUniformIn(Vector3D minValue, Vector3D maxValue, int numPoints)
{
    vector<Vector3D> values;
    values.reserve(numPoints);
    values.resize(numPoints);
    
    double dx = (maxValue[X] - minValue[X]) / (numPoints - 1);
    double dy = (maxValue[Y] - minValue[Y]) / (numPoints - 1);
    double dz = (maxValue[Z] - minValue[Z]) / (numPoints - 1);

    for (int i = 0; i < numPoints; i++)
    {
        double x = minValue[X] + i * dx;
        double y = minValue[Y] + i * dy;
        double z = minValue[Z] + i * dz;
        values[i] = Vector3D(x, y, z);
    }
    return values;
}





vector<Vector3D> getRandomPositions(Vector3D rMinimum, Vector3D rMaximum, int numPoints)
{
    vector<Vector3D> positions;
    positions.reserve(numPoints);
    positions.resize(numPoints);
    for (int i = 0; i < numPoints; i++)
    {
        double xRand = rMinimum[X] + (rMaximum[X] - rMinimum[X]) * ((double)rand() / RAND_MAX);
        double yRand = rMinimum[Y] + (rMaximum[Y] - rMinimum[Y]) * ((double)rand() / RAND_MAX);
        double zRand = rMinimum[Z] + (rMaximum[Z] - rMinimum[Z]) * ((double)rand() / RAND_MAX);
        positions[i] = Vector3D(xRand, yRand, zRand);
    }
    return positions;
}


vector<Vector3D> getRandomVelocities(double temperature, double mass, int numPoints)
{
    vector<Vector3D> velocities;
    velocities.reserve(numPoints);
    velocities.resize(numPoints);

    vector<double> vx = generateMaxwellian(temperature, mass, numPoints);
    vector<double> vy = generateMaxwellian(temperature, mass, numPoints);
    vector<double> vz = generateMaxwellian(temperature, mass, numPoints);
    for (int i = 0; i < numPoints; i++)
        velocities[i] = Vector3D(vx[i], vy[i], vz[i]);
    
    return velocities;
}


vector<Vector3D> getUniformPositions(Vector3D rMinimum, Vector3D rMaximum, int numPoints)
{
    return getUniformIn(rMinimum, rMaximum, numPoints);
}


vector<Vector3D> getUniformVelocities(Vector3D vMinimum, Vector3D vMaximum, int numPoints)
{
    return getUniformIn(vMinimum, vMaximum, numPoints);
}