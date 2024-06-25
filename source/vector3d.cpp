/*
Vector3D.cpp
============
Created: 04.06.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Dedicated descriptor file for Vector3D only.
*/

#include "headers/vector3d.h"




long double &Vector3D::operator[](int i)
{
    switch (i)
    {
    case X:
        return v1;
    case Y:
        return v2;
    case Z:
        return v3;

    default:
        throw out_of_range("INDEX MUST BE 1, 2, or 3");
    }
}

Vector3D Vector3D::operator+(Vector3D other)
{
    return Vector3D(this->v1 + other[X], this->v2 + other[Y], this->v3 + other[Z]);
}

Vector3D Vector3D::operator-(Vector3D other)
{
    return Vector3D(this->v1 - other[X], this->v2 - other[Y], this->v3 - other[Z]);
}

Vector3D Vector3D::operator^(Vector3D other)
{
    Vector3D result;
    result[X] = this->v2 * other[Z] - this->v3 * other[Y];
    result[Y] = this->v3 * other[X] - this->v1 * other[Z];
    result[Z] = this->v1 * other[Y] - this->v2 * other[X];
    return result;
}


Vector3D Vector3D::operator*(double factor)
{
    return Vector3D(this->v1 * factor, this->v2 * factor, this->v3 * factor);
}

Vector3D Vector3D::operator/(double factor)
{
    return Vector3D(this->v1 / factor, this->v2 / factor, this->v3 / factor);
}

long double Vector3D::operator*(Vector3D other)
{
    return (this->v1 * other[X] + this->v2 * other[Y] + this->v3 * other[Z]);
}

bool Vector3D::operator==(Vector3D other)
{
    return (this->v1 == other[X]) && (this->v2 == other[Y]) && (this->v3 == other[Z]);
}

string Vector3D::to_string()
{
    return std::to_string(this->v1) + " i + " + std::to_string(this->v2) + " j + " + std::to_string(this->v3) + " k";
}

long double Vector3D::amplitude()
{
    return sqrt((v1 * v1) + (v2 * v2) + (v3 * v3));
}

long double Vector3D::squareAmp()
{
    return (v1 * v1) + (v2 * v2) + (v3 * v3);
}

void Vector3D::printVector(string name)
{
    cout << endl << scientific
         << name << " = " << this->to_string();
}