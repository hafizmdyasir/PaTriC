/*
MISC.cpp
========
Created: 23.04.2025

Copyright
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Miscellaneous descriptions
*/

#include <algorithm>
#include <iostream>
#include <unistd.h>

#include "misc.h"

using namespace std;


/// @brief Print the initial header.
void printHeader()
{
     cout << " ####        #######                 ####   \n"
          << "#    #          #                   #    #  \n"
          << "#    #          #                   #       \n"
          << "#####   ###     #     ###   #####   #       \n"
          << "#      #   #    #    #   #    #     #       \n"
          << "#      #####    #    ####     #     #    #  \n"
          << "#      #   #    #    #   #  #####    ####   \n"
          << "__________________________________________\n"
          
          << "Particle Tracker in C++"
          << "\nVersion " << VERSION
          << "\n\nBy Mohammad Yasir"
          << "\nIIT Delhi\n" << endl;
}



bool contains(vector<string> vec, string element)
{
    return count(vec.begin(), vec.end(), element) > 0;
}


bool startsWith(const string& str, const string& prefix) {
    return str.substr(0, prefix.size()) == prefix;
}


string formatDuration(chrono::milliseconds ms) 
{
    auto hours = chrono::duration_cast<chrono::hours>(ms);
    ms -= hours;

    auto minutes = chrono::duration_cast<chrono::minutes>(ms);
    ms -= minutes;

    auto seconds = chrono::duration_cast<chrono::seconds>(ms);
    ms -= seconds;

    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(ms);

    ostringstream oss;

    if (hours.count() > 0)
        oss << hours.count() << " hours, ";
    
    if (minutes.count() > 0)
        oss << minutes.count() << " minutes, ";
    
    oss << seconds.count();

    if (milliseconds.count() > 0)
        oss << "." << setw(5) << setfill('0') << milliseconds.count() << " seconds";

    return oss.str();
}