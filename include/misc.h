/*
MISC.h
======
Created: 23.04.2025

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Helper functions. Must not include any dependency on PaTriC library.
*/

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>

#define VERSION "2.0.0"



using namespace std;


bool startsWith(const string& str, const string& prefix);


bool contains(vector<string> vec, string element);


void printHeader();


string formatDuration(chrono::milliseconds ms);