/*
INTEGRATOR.cpp
==============
Created: 17.04.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Definitions of integrators.
*/


#include "headers/integrator.h"
#include "headers/config.h"

// q*dt/2m
double factor = NAN;

void presetIntegrators(Particles particle, double deltaT)
{
    factor = (particle.charge * deltaT / (2*particle.mass));
}


Vector3D borisIntegrator(Vector3D eField, Vector3D magField, Vector3D previousU)
{
    Vector3D u_minus = previousU + (eField*factor);
    double gamma_minus = sqrt(1 + (u_minus/constants::c).squareAmp());

    Vector3D t = magField*(factor/gamma_minus); 
    Vector3D s = t * (2/(1 + t.squareAmp()));

    Vector3D u_prime = u_minus + (u_minus ^ t);
    Vector3D u_plus = u_minus + (u_prime ^ s);

    Vector3D u_next = u_plus + (eField*factor);
    Vector3D v_next = u_next * (constants::c / sqrt(constants::c2 + u_next.squareAmp()));
    currentGamma = 1 / sqrt(1 - v_next.squareAmp()/constants::c2);
    return u_next;
}


Vector3D vayIntegrator(Vector3D eField, Vector3D magField, Vector3D previousU)
{
    Vector3D fieldContri = eField + ((previousU ^ magField) / currentGamma);
    Vector3D u_next_half = previousU + (fieldContri * factor);

    Vector3D tau = magField*factor;
    Vector3D u_prime = u_next_half + (eField*factor);

    float u_star = u_prime*(tau/constants::c);
    float gamma_prime = sqrt(1 + u_prime.squareAmp()/constants::c2);
    float sigma = (gamma_prime*gamma_prime) - tau.squareAmp();
    float gamma_next = sqrt(0.5  * (sigma + sqrt(sigma*sigma + 4*(tau.squareAmp() + u_star*u_star))));
    Vector3D t = tau/gamma_next;

    double s = 1 / (1 + t.squareAmp());
    double value = u_prime*t;

    Vector3D bracketTerm = u_prime + t*value + (u_prime ^ t);
    Vector3D u_next = bracketTerm*s;
    currentGamma = gamma_next;
    return u_next;


    /* Vector3D fieldContri = eField + cross(previousV, magField);
    Vector3D v_next_half = previousV + fieldContri*factor;

    Vector3D tau = magField*factor;
    Vector3D e = eField*factor;
    Vector3D v_prime = v_next_half + e;

    double s = 1 / (1 + tau.squareAmp());
    double value = v_prime*tau;

    Vector3D bracketTerm = v_prime + tau*value + cross(v_prime, tau);
    Vector3D v_next = bracketTerm*s;

    return v_next; */
}


Vector3D higueraCary(Vector3D eField, Vector3D magField, Vector3D previousU)
{
    Vector3D u_minus = previousU + eField*factor;
    double gamma_minus = sqrt(1 + u_minus.squareAmp()/constants::c2);
    
    Vector3D tau = magField*factor;
    double u_star = u_minus * (tau/constants::c);
    double sigma = (gamma_minus*gamma_minus) - tau.squareAmp();
    double gamma_plus = sqrt(0.5 * (sigma + sqrt(sigma*sigma + 4*(tau.squareAmp() + u_star*u_star))));


    Vector3D t = tau / gamma_plus;
    double s = 1 / (1 + t.squareAmp());
    double dotProd = u_minus*t;

    Vector3D bracketTerm = u_minus + t*dotProd + (u_minus ^ t);
    Vector3D u_plus = bracketTerm*s;

    Vector3D u_next = u_plus + eField*factor + (u_minus ^ t);
    Vector3D v_next = u_next * (constants::c / sqrt(constants::c2 + u_next.squareAmp()));
    currentGamma = 1 / sqrt(1 - v_next.squareAmp()/constants::c2);

    return u_next;
}