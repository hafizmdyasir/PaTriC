'''
DECK TOOLS.py
=============
Created: 13.06.2024

Copyright
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Insert defaults and validate deck
'''

# Add the script path temporarily to import path so that the modules are resolved.
from os.path import dirname, abspath
script_dir = dirname(abspath(__file__))
from sys import path
path.insert(0, script_dir+'/pypatric')
path.insert(0, script_dir)

from pypatric.keys import *
from pypatric.classes import *


def __insertIfNotExists(dictionary: dict, key: str, value):
    '''Insert a value into the dictionary only if not present.'''
    if key not in dictionary.keys():
        dictionary[key] = value




def insertDefaults(control: dict, particle: dict, fields: dict, output: dict):
    '''Check and insert defaults in the deck.'''

    # Validate control deck
    control[NUM_ITERS] = int(control[NUM_ITERS])
    control[READOUT_FREQ] = int(control[READOUT_FREQ])
    control[INTEGRATOR] = int(control[INTEGRATOR])
    
    # Particle dict
    particle[MASS] = float(particle[MASS])
    particle[CHARGE] = float(particle[CHARGE])
    
    __insertIfNotExists(particle, PARTICLE_COUNT, 1)
    __insertIfNotExists(fields, E_FIELD, tuple([]))
    __insertIfNotExists(fields, B_FIELD, tuple([]))

    # Output dict
    __insertIfNotExists(output, FILEPATH, '')
    __insertIfNotExists(output, DUMP_INFO_FILE, True)
    __insertIfNotExists(output, FILE_HEADER, tuple([]))

    if (len(output[FILEPATH]) > 0) and not str(output[FILEPATH]).endswith('/'):
        output[FILEPATH] = output[FILEPATH] + '/'
