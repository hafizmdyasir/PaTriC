/*
PYTHON SERVER.cpp
=================
Created: 27.06.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Server that forks up a python process and calculates fields as required.
*/


#include "headers/pythonserver.h"




PythonServer::PythonServer(const string& _sname, const string& _dpath): scriptName(_sname), deckPath(_dpath), pid(-1)
{
    // Create the pipes
    if (pipe(inputPipe) == -1 || pipe(outputPipe) == -1)
        throw runtime_error("Failed to create pipes for reading and writing");

    // Fork process and act depending on where one is.
    pid = fork();
    switch (pid)
    {
    case -1:
        throw runtime_error("Failed to fork the process");
        break;

    case 0:
        // In child process
        close(inputPipe[1]);
        close(outputPipe[0]);

        dup2(inputPipe[0], STDIN_FILENO);
        dup2(outputPipe[1], STDOUT_FILENO);

        // The magic happens here
        execlp("python3", "python3", scriptName.c_str(), "-f", deckPath.c_str(), (char*)NULL);
        throw runtime_error("Failed to execute python process");
        break;
    
    default:
        // In parent process
        close(inputPipe[0]);
        close(outputPipe[1]);
        break;
    }
}

PythonServer::~PythonServer()
{
    close(inputPipe[1]);
    close(outputPipe[0]);
    kill(pid, SIGTERM);
    waitpid(pid, nullptr, 0);
}

vector<string> PythonServer::split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

bool PythonServer::writeInput(const string& input) {
    ssize_t bytesWritten = write(inputPipe[1], input.c_str(), input.size());
    return bytesWritten == (ssize_t)input.size();
}

bool PythonServer::readOutput(string& output) {
    char buffer[128];
    ssize_t bytesRead = read(outputPipe[0], buffer, sizeof(buffer) - 1);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        output = buffer;
        return true;
    }
    return false;
}


bool PythonServer::callFunction(string functionName, Vector3D position, float time, Vector3D& result) {
    ostringstream oss;
    oss << functionName << " " << position[X] << " " << position[Y] << " " << position[Z] << " " << time << "\n";
    if (!writeInput(oss.str())) {
        return false;
    }

    string output;
    if (!readOutput(output)) {
        return false;
    }

    vector<string> results = split(output, ' ');
    if (results.size() != 3) {
        return false;
    }

    try {
        float out1 = stof(results[0]);
        float out2 = stof(results[1]);
        float out3 = stof(results[2]);
        
        result[X] = out1;
        result[Y] = out2;
        result[Z] = out3;

    } catch (...) {
        return false;
    }

    return true;
}