/*
PARSER.cpp
==========
Created: 16.05.2024

Copyright
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Functions that will aid in parsing python file. Read README to learn more.
*/

#include "headers/initializer.h"
#include "headers/constants.h"
#include "headers/classes.h"
#include "headers/parser.h"
#include "headers/config.h"
#include "headers/misc.h"

void readFromDump(string dumpName, unordered_map<string, string> &dataDump)
{
    ifstream dumpFile(dumpName);
    string line;

    while (getline(dumpFile, line))
    {
        if (line.find('#') == 0 || line.find(':') == -1)
            continue;

        int colonIndex = line.find(":");
        string key = line.substr(0, colonIndex);
        string value = line.substr(colonIndex + 2, line.length());
        dataDump[key] = value;
    }
    dumpFile.close();
    remove(dumpName.c_str());
}

Control processControl(unordered_map<string, string> &dataDump)
{
    float dt = stof(dataDump[TIME_STEP]);
    int iters = stoi(dataDump[NUM_ITERS]);
    int integ = stoi(dataDump[INTEGRATOR]);
    int outfreq = stoi(dataDump[READOUT_FREQ]);
    return Control(dt, integ, iters, outfreq);
}

Particles processParticles(unordered_map<string, string> &dataDump)
{
    float mass = stof(dataDump[MASS]);
    float charge = stof(dataDump[CHARGE]);
    int particleCount = stoi(dataDump[PARTICLE_COUNT]);

    string velInit = dataDump[INITIAL_VELOCITY];
    string posInit = dataDump[INITIAL_POSITION];

    vector<Vector3D> positions;
    vector<Vector3D> velocities;
    positions.reserve(particleCount);
    velocities.reserve(particleCount);

    // The posInit and velInit variable is sure to be a tuple containing object(s) of custom type. This is ensured in the deck_tools file.
    // We extract each item here.
    vector<ParsedType> parsedPositions = extractTypes(posInit);
    vector<ParsedType> parsedVelocities = extractTypes(velInit); // Same for velocities.

    // Now, loop over the positions and check which type is requested.
    for (ParsedType type : parsedPositions)
    {
        string typeName = type.className;
        vector<float> params = type.parameters;

        if (typeName == "Uniform")
        {
            positions = getUniformPositions(
                Vector3D(params[0], params[1], params[2]),
                Vector3D(params[3], params[4], params[5]), particleCount);
            break;
        }
        if (typeName == "Random")
        {
            positions = getRandomPositions(
                Vector3D(params[0], params[1], params[2]),
                Vector3D(params[3], params[4], params[5]),
                particleCount);
            break;
        }
        positions.push_back(Vector3D(params[0], params[1], params[2]));
    }

    for (ParsedType vel : parsedVelocities)
    {
        string typeName = vel.className;
        vector<float> params = vel.parameters;

        if (typeName == "Uniform")
        {
            velocities = getUniformVelocities(
                Vector3D(params[0], params[1], params[2]),
                Vector3D(params[3], params[4], params[5]), particleCount);
            break;
        }
        if (typeName == "Maxwellian")
        {
            velocities = getRandomVelocities(params[0], mass * constants::m_e, particleCount);
            break;
        }
        velocities.push_back(Vector3D(params[0], params[1], params[2]));
    }

    return Particles(mass, charge, particleCount, positions, velocities);
}

Fields processFields(unordered_map<string, string> &dataDump)
{
    string eField = dataDump[E_FIELD];
    string bField = dataDump[B_FIELD];

    vector<Geometry *> bFieldGeometries;
    if (bField == "getBField")
        bFieldGeometries.push_back(new CustomGeometry(bField));
    else
    {
        vector<ParsedType> providedGeometries = extractTypes(bField);
        bFieldGeometries.reserve(providedGeometries.size());

        for (const ParsedType &geometry : providedGeometries)
        {
            string name = geometry.className;
            vector<float> params = geometry.parameters;
            if (name == "Static")
                bFieldGeometries.push_back(new StaticGeometry(params[0], params[1], params[2]));
            else if (name == "Coil")
                bFieldGeometries.push_back(new MagneticCoil(params[0], params[1], params[2]));
            else if (name == "Wire")
            {
                Vector3D midpoint = Vector3D(params[3], params[4], params[5]);
                bFieldGeometries.push_back(new MagneticWire(params[0], params[1], midpoint, params[6]));
            }
        }
    }

    vector<Geometry *> eFieldGeometries;
    if (eField == "getEField")
        eFieldGeometries.push_back(new CustomGeometry(eField));
    else
    {
        vector<ParsedType> eFieldProvided = extractTypes(eField);
        eFieldGeometries.reserve(eField.size());

        for (const ParsedType &geometry : eFieldProvided)
        {
            string name = geometry.className;
            vector<float> params = geometry.parameters;
            if (name == "Static")
                eFieldGeometries.push_back(new StaticGeometry(params[0], params[1], params[2]));
        }
    }

    return Fields(eFieldGeometries, bFieldGeometries);
}

Output processOutputInfo(unordered_map<string, string> &dataDump)
{
    string fileName = dataDump[FILENAME];
    string outputPath = dataDump[FILEPATH];
    bool infoDump = (dataDump[DUMP_INFO_FILE] == "True");
    vector<string> headers = parseStringTuple(dataDump[FILE_HEADER]);
    vector<string> dumpVars = parseStringTuple(dataDump[DUMP_VARIABLES]);
    return Output(fileName, outputPath, headers, infoDump, dumpVars);
}

void processDumpMap(unordered_map<string, string> &dataDump)
{
    Control control = processControl(dataDump);
    Particles particles = processParticles(dataDump);
    Fields fields = processFields(dataDump);
    Output out = processOutputInfo(dataDump);
    initialize(control, particles, fields, out);
}

bool parseFile(string fullpath)
{
    unordered_map<string, string> dataDump;
    string command = "python3 " + execPath + "/pyparser.py -f " + inputDeckPath;
    int configRead = system(command.c_str());
    if (configRead != 0)
    {
        cerr << endl
             << "The program encountered the above mentioned error and will now terminate... " << endl;
        return false;
    }
    readFromDump("config.dmp", dataDump);
    processDumpMap(dataDump);
    return true;
}
