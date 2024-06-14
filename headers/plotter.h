/*
PLOTTER.h
=========
Created: 18.05.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Helper functions for plotting.
*/

#ifndef PLOTTER_H
#define PLOTTER_H

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

#include "classes.h"
#include "misc.h"

using namespace std;



void saveData(vector<Vector3D>& positions, vector<Vector3D>& velocities, Output outputInfo, float dt, int count);
void saveInfo(Output outputInfo, Control control, Particles particles, float tt);


#endif /* PLOTTER_H */