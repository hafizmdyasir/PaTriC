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




PythonServer::PythonServer(string& _dpath): deckPath(_dpath), pid(-1)
{
    startServer(_dpath);
}

PythonServer::~PythonServer()
{
    close(inputPipe[1]);
    close(outputPipe[0]);
    kill(pid, SIGTERM);
    waitpid(pid, nullptr, 0);
}

void PythonServer::startServer(const string& _dpath)
{
    deckPath = _dpath;
    // Create the pipes
    if (pipe(inputPipe) == -1 || pipe(outputPipe) == -1)
        throw runtime_error("Failed to create pipes for reading and writing");

    // Fork process and act depending on where one is.
    pid = fork();
    if (pid == -1) {
        throw runtime_error("Failed to fork process");
    } else if (pid == 0) {
        // Child process
        close(inputPipe[1]);
        close(outputPipe[0]);

        dup2(inputPipe[0], STDIN_FILENO);
        dup2(outputPipe[1], STDOUT_FILENO);

        // Using execvp to handle paths with spaces
        char* args[] = {
            const_cast<char*>("python3"),
            const_cast<char*>("-u"),
            const_cast<char*>("pyserver.py"),
            const_cast<char*>("-f"),
            const_cast<char*>(deckPath.c_str()),
            nullptr
        };

        execvp("python3", args);
        // If execvp returns, it must have failed.
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(inputPipe[0]);
        close(outputPipe[1]);
    }
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