/*
Vector3D.h
==========
Created: 23.04.2025

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Dedicated header file for Vector3D only.
*/


#pragma once

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <math.h>

#include "constants.h"

using namespace std;




class Vector3D
{
public:
    real v1;
    real v2;
    real v3;

    Vector3D()
        : v1(0.0), v2(0.0), v3(0.0) {}

    Vector3D(real _v1, real _v2, real _v3)
        : v1(_v1), v2(_v2), v3(_v3) {}
    
    Vector3D(const Vector3D& other)
        : v1(other.v1), v2(other.v2), v3(other.v3) {}
    
    Vector3D(vector<real> vals)
        : v1(vals[0]), v2(vals[1]), v3(vals[2]) {}

    // Add two vectors
    Vector3D operator+(Vector3D other);
    
    // Subtract two vectors
    Vector3D operator-(Vector3D other);

    // Cross-product of two vectors
    Vector3D operator^(Vector3D other);
    
    // Multiply the vector with a scalar.
    Vector3D operator*(real factor);
    
    // Divide the vector by a scalar. 
    Vector3D operator/(real factor);
    
    // Check if two vectors are equal. Return true if and only if all components are equal.
    bool operator==(Vector3D other);

    // Dot product of two vectors.
    real operator*(Vector3D other);

    // Get particular components using indexing X = 0, Y = 1, Z = 2.
    real& operator[] (int i);
    
    // cout the vector, with optional argument to print a name before it.
    void printVector(string name = "") const;

    // String representation in terms of i, j, and k.
    string to_string() const;
    
    // Get the magnitude of the vector.
    real amplitude() const;

    // Get the square of the magnitude of the vector.
    real squareAmp() const;
};