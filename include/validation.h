/*
VALIDATION.h
============
Created: 12.10.2026

Copyright 
Mohammad Yasir
Indian Institute of Technology, Delhi

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Declares helper functions to confirm initial conditions are valid.
*/

#pragma once

#include "classes.h"

bool validateInitialConditions(Control* control, Particle* target, Fields* fields, Output* output);