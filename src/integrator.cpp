/*
INTEGRATOR.cpp
==============
Created: 24.04.2025

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Definitions of integrators.
*/


#include "integrator.h"



string getIntegratorName(Pusher integrator)
{
    return string(INTEGRATORS[static_cast<int>(integrator)]);
}


// q*dt/2m
real factor = NAN;

void presetIntegrators(Particle particle, real deltaT)
{
    factor = (particle.charge * deltaT / (2*particle.mass));
}

Integrator Boris = [](Vector3D eField, Vector3D magField, Vector3D previousU) -> Momentum {
    Vector3D u_minus = previousU + (eField*factor);
    real gamma_minus = sqrt(1 + (u_minus.squareAmp()/constants::c2));

    Vector3D t = magField*(factor/gamma_minus); 
    Vector3D s = t * (2/(1 + t.squareAmp()));

    Vector3D u_prime = u_minus + (u_minus ^ t);
    Vector3D u_plus = u_minus + (u_prime ^ s);

    Vector3D u_next = u_plus + (eField*factor);
    Vector3D v_next = u_next * (constants::c / sqrt(constants::c2 + u_next.squareAmp()));
    return Momentum(v_next, 1 / sqrt(1 - v_next.squareAmp()/constants::c2));
};


Integrator Vay = [](Vector3D eField, Vector3D magField, Vector3D previousU) -> Momentum {
    real currentGamma = 1 / sqrt(1 - previousU.squareAmp() / constants::c2);
    Vector3D fieldContri = eField + ((previousU ^ magField) / currentGamma);
    Vector3D u_next_half = previousU + (fieldContri * factor);

    Vector3D tau = magField*factor;
    real tau2 = tau.squareAmp();

    Vector3D u_prime = u_next_half + (eField*factor);

    real u_star = (u_prime*tau)/constants::c;
    real gamma_prime = sqrt(1 + u_prime.squareAmp()/constants::c2);
    real sigma = (gamma_prime*gamma_prime) - tau2;
    real gamma_next = sqrt(0.5  * (sigma + sqrt(sigma*sigma + 4*(tau2 + u_star*u_star))));
    Vector3D t = tau/gamma_next;

    real s = 1 / (1 + t.squareAmp());
    real value = u_prime*t;

    Vector3D bracketTerm = u_prime + t*value + (u_prime ^ t);
    Vector3D u_next = bracketTerm*s;
    Vector3D v_next = u_next * (constants::c / sqrt(constants::c2 + u_next.squareAmp()));
    return Momentum(v_next, gamma_next);
};


Integrator HigueraCary = [](Vector3D eField, Vector3D magField, Vector3D previousU) -> Momentum {
    Vector3D u_minus = previousU + (eField*factor);
    real gamma_minus = sqrt(1 + (u_minus.squareAmp()/constants::c2));
    
    Vector3D tau = magField*factor;
    real tau2 = tau.squareAmp();

    real u_star = (u_minus * tau)/constants::c;
    real sigma = (gamma_minus*gamma_minus) - tau2;
    real gamma_plus = sqrt(0.5 * (sigma + sqrt(sigma*sigma + 4*(tau2 + (u_star*u_star)))));

    Vector3D t = tau / gamma_plus;
    real s = 1 / (1 + t.squareAmp());

    Vector3D bracketTerm = u_minus + (t*(u_minus*t)) + (u_minus ^ t);
    Vector3D u_plus = bracketTerm*s;

    Vector3D u_next = u_plus + (eField*factor) + (u_plus ^ t);
    Vector3D v_next = u_next * (constants::c / sqrt(constants::c2 + u_next.squareAmp()));
    
    return Momentum(v_next, 1 / sqrt(1 - v_next.squareAmp()/constants::c2));
};