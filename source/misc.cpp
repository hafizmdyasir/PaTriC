/*
MISC.cpp
========
Created: 21.02.2024

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
#include <math.h>
#include <vector>
#include <regex>

#include "headers/misc.h"

using namespace std;


/// @brief Print the initial header.
void printHeader()
{
     clearScreen();
     cout << " ####        #######                 ####   " << endl
          << "#    #          #                   #    #  " << endl
          << "#    #          #                   #       " << endl
          << "#####   ###     #     ###   #####   #       " << endl
          << "#      #   #    #    #   #    #     #       " << endl
          << "#      #####    #    ####     #     #    #  " << endl
          << "#      #   #    #    #   #  #####    ####   " << endl;

     cout << endl << "Particle Tracker in C++"
          << endl
          << "By Mohammad Yasir"
          << endl
          << "Research Scholar"
          << endl
          << "IIT Delhi \n";
}


string getIntegratorName(int input)
{
    switch (input)
     {
     case 0:
     default:
          return "Boris";
          break;

     case 1:
          return "Vay";
          break;

     case 2:
          return "Higuera Cary";
          break;
     }
}



bool contains(vector<string> vec, string element)
{
    return count(vec.begin(), vec.end(), element) > 0;
}


bool startsWith(const string& str, const string& prefix) {
    return str.substr(0, prefix.size()) == prefix;
}


bool isWindowsSystem()
{
     #ifdef WINDOWS
     return true;
     #endif
     
     #ifdef WINDOWS_
     return true;
     #endif
     
     #ifdef _WIN32
     return true;
     #endif
     
     return false;
}


void clearScreen()
{
    if (isWindowsSystem()) system("cls");
    else system("clear");
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
        oss << "." << setw(3) << setfill('0') << milliseconds.count() << " seconds";

    return oss.str();
}


vector<float> parseFloatTuple(const string tupleStr) {
    vector<float> values;
    values.clear();

    regex floatRegex(R"(\s*([-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?)\s*)");
    smatch match;

    // Remove the parentheses
    string content = tupleStr.substr(1, tupleStr.size() - 2);

    // Using a regex iterator to find all float values in the content
    string::const_iterator searchStart(content.cbegin());
    while (regex_search(searchStart, content.cend(), match, floatRegex)) {
        values.push_back(stof(match[1]));
        // Move the search start past the last match
        searchStart = match.suffix().first;
    }
    return values;
}



vector<string> parseStringTuple(const string tupleStr) {
    vector<string> values;
    values.clear();

    regex re(R"(["']([^"']*)["'])"); // Regex to match strings inside quotes
    auto begin = sregex_iterator(tupleStr.begin(), tupleStr.end(), re);
    auto end = sregex_iterator();

    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        values.push_back(match.str(1)); // Extract the matched string without quotes
    }

    return values;
}



vector<string> extractTuples(const string tuplesString) {
    
    vector<string> tuples;
    regex tuple_regex(R"(\(\s*[^()]*\s*\))");
    smatch match;
    string s = tuplesString;

    while (regex_search(s, match, tuple_regex)) {
        tuples.push_back(match.str(0));
        s = match.suffix();
    }

    return tuples;
}


vector<ParsedType> extractTypes(string tuplesString) {
    
    vector<ParsedType> instances;
    
    // Regular expression to match ClassName(parameters)
    regex class_regex(R"((\w+)\s*\(([^()]*)\))");
    smatch match;

    // Remove the outer brackets if present
    if (tuplesString.front() == '(' && tuplesString.back() == ')') {
        tuplesString = tuplesString.substr(1, tuplesString.size() - 2);
    }

    while (regex_search(tuplesString, match, class_regex)) {
        ParsedType instance(match[1].str(), parseFloatTuple("(" + match[2].str() + ")"));        
        instances.push_back(instance);
        tuplesString = match.suffix().str();
    }

    return instances;
}