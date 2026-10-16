/*
INPUT.cpp
=========

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Benchmark input script for PaTriC that sets up 100 random particles with velocity perpendicular to magnetic field. The particles should gyrate and not gain energy.
*/
#include <patric.h>

extern "C" {

    /// @brief This function is called to configure the simulation.
    /// @param ctrl The control object which sets up timestep, simulation time, and particle pusher.
    /// @param prtcl The particle object which sets up particle count, charge, mass, and initial conditions.
    /// @param fields The fields object which sets up the electric and magnetic fields.
    /// @param output The output object which sets up the output file and format.
    void configureSimulation(Control*& ctrl, Particle*& prtcl, Fields*& fields, Output*& output) {
        // ... fill out parameters ...
        float timestep = 0.001;
        float simulationTime = 1000;
        Pusher particlePusher = Pusher::Boris;

        // Control parameters are defined this way.
        ctrl = new Control(0.001, 1000, particlePusher);


        unsigned int particleCount = 100;
        float particleCharge = 1.0;
        float particleMass = 1.0;
        vector<Vector3D> initialPositions = getRandomIC(particleCount, -0.0001, 0.0001, -0.0001, 0.0001, -0.0001, 0.0001);
        vector<Vector3D> initialVelocities = getRandomIC(particleCount, -0.0001, 0.0001, -0.0001, 0.0001, 0,0);
        
        // Particle parameters are defined this way. You can use helper functions to generate initial conditions.
        prtcl = new Particle(
            particleCount, particleCharge, particleMass, 
            initialPositions, initialVelocities);


        FieldGetter electricField = getConstantField(Vector3D(0,0,0));
        FieldGetter magneticField = getConstantField(Vector3D(0,0,1));
        
        // Fields parameters are defined this way. You can use helper functions to generate fields.
        // Leave blank for no field.
        fields = new Fields(electricField, magneticField);

        // Output parameters are defined this way. You can customize the output format and file name.
        string outputFileName = "output";
        string outputFilePath = "./data/";
        unsigned int outputFrequency = 20;
        vector<string> outputVariables = {POS_X, POS_Y, POS_Z, VEL_X, VEL_Y, VEL_Z};
        output = new Output(outputFileName, outputFilePath, outputFrequency, outputVariables);
    }
}