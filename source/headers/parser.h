/*
PARSER.h
========
Created: 18.05.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Parses the temp dump file for initializing system.
*/


#ifndef PARSER_H
#define PARSER_H


#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <regex>


#include "constants.h"
#include "geometry.h"

using namespace std;


bool parseFile();

#endif /* PARSER_H */