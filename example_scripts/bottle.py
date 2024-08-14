'''
BOTTLE.py
=========
Created: 14.08.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
This is an example input script for PaTriC that simulates the motion of an electron in a magnetic bottle created by using two magnetic coils.
'''

# Import the necessary module
# Always import everything from this module.
from deck_helper import *

# Define the bottle parameters
bottle_radius = 0.05
bottle_length = 0.5
coil_current = 1e4


createControl(
    timeStep=1e-10, numiterations=4000, 
    integrator=BORIS, readoutFreq=0)

createParticles(mass=1, charge=-1, particleCount=1, 
                initialPosition=(Static(0,0,0), ), initialVelocity=(Static(5.66e5, 1.82e6, 3.84e6), ))

createFields(electricFields=(), magneticFields=mFields)

createOutput(fileName='bottle', filePath='bottle_simulations', 
             fileHeaders=('MAGNETIC BOTTLE SIMULATIONS', '1 Particle Used'), 
             dumpInfoFile=True, dumpVariables=(POS_X, POS_Y, POS_Z))