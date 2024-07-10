/*
Vector3D.h
==========
Created: 04.06.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Dedicated header file for Vector3D only.
*/


#ifndef VECTOR3D_H
#define VECTOR3D_H

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
    long double v1;
    long double v2;
    long double v3;

    Vector3D()
        : v1(0.0), v2(0.0), v3(0.0) {}

    Vector3D(long double _v1, long double _v2, long double _v3)
        : v1(_v1), v2(_v2), v3(_v3) {}
    
    Vector3D(const Vector3D& other)
        : v1(other.v1), v2(other.v2), v3(other.v3) {}
    
    Vector3D(vector<float> vals)
        : v1(vals[0]), v2(vals[1]), v3(vals[2]) {}

    // Add two vectors
    Vector3D operator+(Vector3D other);
    
    // Subtract two vectors
    Vector3D operator-(Vector3D other);

    // Cross-product of two vectors
    Vector3D operator^(Vector3D other);
    
    // Multiply the vector with a scalar.
    Vector3D operator*(double factor);
    
    // Divide the vector by a scalar. 
    Vector3D operator/(double factor);
    
    // Check if two vectors are equal. Return true if and only if all components are equal.
    bool operator==(Vector3D other);

    // Dot product of two vectors.
    long double operator*(Vector3D other);

    // Get particular components using indexing X = 1 , Y = 2, Z = 3.
    long double& operator[] (int i);
    
    // cout the vector, with optional argument to print a name before it.
    void printVector(string name = "");

    // String representation in terms of i, j, and k.
    string to_string();
    
    // Get the magnitude of the vector.
    long double amplitude();

    // Get the square of the magnitude of the vector.
    long double squareAmp();
};


#endif