/*
PLOTTER.cpp
===========
Created: 18.05.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Helper functions for plotting
*/

#include "classes.h"

#include <filesystem>
#include <fstream>


int setupDiagnostic(Output outputInfo, int particleNumber);
void saveData(vector<Vector3D>& positions, vector<Momentum>& momenta, vector<Vector3D> eFields, vector<Vector3D> mFields, Output outputInfo, int particleNumber, int dumpNumber);
