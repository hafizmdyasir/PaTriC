/*
FIELDS.cpp
==========
Created: 09.10.2026

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Defines function that can be used to calculate fields.
*/

#include "fields.h"

/// @brief Returns a field getter that returns a constant vector.
/// @param components The constant vector to return.
/// @return A field getter that returns the constant vector.
FieldGetter getConstantField(Vector3D components) {
    return [components](Vector3D position, real time) {
        return components;
    };
}

/// @brief Returns a field getter that returns a sine wave field. The wave is driven as
/// amplitude * sin(frequency * variable + phase) in the direction of the given vector.
/// @param amplitude The amplitude of the sine wave.
/// @param frequency The frequency of the sine wave. 
/// @param phase The phase of the sine wave.
/// @param variable The variable to use for the sine wave.
/// @param direction The direction of the sine wave.
/// @return A field getter that returns the sine wave field.
FieldGetter getSineField(real amplitude, real frequency, real phase, int variable, Vector3D direction) {
    if (variable != T && variable != X && variable != Y && variable != Z) {
        throw std::invalid_argument("Invalid variable for sine field input. Must be T, X, Y, or Z.");
    }

    return [amplitude, frequency, phase, variable, direction](Vector3D position, real time) {
        real input = NAN;
        if (variable == T) input = time;
        else input = position[variable];

        real value = amplitude * sin(frequency * input + phase);
        return Vector3D(direction)*value;
    };
}



/// @brief Returns a field getter that returns a Gaussian field. The field is driven as
/// amplitude * exp(-((variable - center)^2) / (2 * sigma^2)) in the direction of the given vector.
/// @param amplitude The amplitude of the Gaussian field.
/// @param sigma The standard deviation of the Gaussian field.
/// @param center The center of the Gaussian field.
/// @param power The exponent for the Gaussian. 2 means Gaussian, 1 means exponential decay, etc.
/// @param variable The variable to use for the Gaussian field.
/// @param direction The direction of the Gaussian field.
/// @return A field getter that returns the Gaussian field.
FieldGetter getGaussianField(real amplitude, real sigma, real center, float power, int variable, Vector3D direction) {
    if (variable != T && variable != X && variable != Y && variable != Z) {
        throw std::invalid_argument("Invalid variable for Gaussian field input. Must be T, X, Y, or Z.");
    }

    return [=](Vector3D position, real time) {
        real input = NAN;
        if (variable == T) input = time;
        else input = position[variable];

        real value = amplitude * exp(-pow((input - center), power) / (2 * pow(sigma, power)));
        return Vector3D(direction)*value;
    };
}