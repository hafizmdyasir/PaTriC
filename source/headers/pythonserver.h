/*
PYTHON SERVER.h
===============
Created: 27.06.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Server that forks up a python process and calculates fields as required.
*/

#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <string>
#include <vector>

#include "vector3d.h"


using namespace std;


/// @brief This class represents a server that can fork up a python subprocess and use pipes to communicate with it.
class PythonServer
{
private:
    string deckPath;
    int inputPipe[2];
    int outputPipe[2];
    pid_t pid;

    /// @brief Split a string into a vector of strings using the provided delimiter.
    /// @param str The string to be split.
    /// @param delimiter The delimiter to be used.
    /// @return A vector of strings containing the splitted string.
    vector<string> split(const string& str, char delimiter);

    /// @brief Write the input to the pipe
    /// @param input The input string
    /// @return true if the write process succeeded.
    bool writeInput(const string& input);

    /// @brief Read result containing three floating point values from the pipe and write it to the string provided.
    /// @param outputString the string where result must be written.
    /// @return true if the read process succeeded.
    bool readOutput(string& outputString);

public:
    PythonServer() {}
    PythonServer(string& _dpath);
    ~PythonServer();

    /// @brief Use this function to calculate the fields at the given position and time.
    /// @param position Vector3D object representing our target's current position.
    /// @param time floating point value of current time
    /// @param result The Vector3D object where result will be stored.
    /// @return true if the read process succeeded
    bool callFunction(string functionName, Vector3D position, float time, Vector3D& result);

    void startServer(const string& _deckPath);
};




#endif // SERVER_H