/*
MISC.h
======
Created: 21.02.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Helper functions. Must not include any dependency on PaTriC library.
*/

#ifndef MISC_H
#define MISC_H

#include <vector>
#include <string>


using namespace std;


string getIntegratorName(int input);


bool startsWith(const std::string& str, const std::string& prefix);


bool contains(vector<string> vec, string element);


void clearScreen();


void printHeader();


/// @brief Extract floats from a tuple of strings.
/// @param tupleStr The tuple of floats.
/// @return A vector containing each entry from the tuple.
vector<float> parseFloatTuple(const string tupleStr);


/// @brief Extract strings from a tuple of strings.
/// @param tupleStr The tuple of strings
/// @return A vector containing each entry from the tuple.
vector<string> parseStringTuple(const string tupleStr);


/// @brief Extract each tuple from a string containing tuple of tuples and return in a vector form.
/// @param tuplesString The string containing the tuple.
/// @return The vector containing the tuples inside the tuple string provided.
vector<string> extractTuples(const string tuplesString);



/// @brief Represents a class in terms of its name and floating point type parameters.
class ParsedType
{
public:
    string className;
    vector<float> parameters;
    ParsedType() {}
    ParsedType(string _name, vector<float> _params)
        : className(_name), parameters(_params) {}
};


/// @brief From the given string, which could be a tuple of entries or could be a single entry, extract the entry. Each entry in this tuple corresponds to an object description of the form className(parameters), where each parameter is a float.
/// @param tuplesString The string to extract the entries from.
/// @return A vector of type ParsedType that contains the class name and the parameters.
vector<ParsedType> extractTypes(string tuplesString);

#endif