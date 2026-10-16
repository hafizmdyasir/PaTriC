/*
PATRIC.h
========
Created: 07.10.2026

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
This is a configuration file to be set up for dynamic linking when the user runs the program. It contains simulation starting information.
*/

#pragma once

#include "classes.h"
#include "fields.h"
#include "initial_condition.h"

// The C-style bridge function signature that the loader will look for
extern "C" {
    typedef void (*ConfigurePatric)(Control*&, Particle*&, Fields*&, Output*&);
}