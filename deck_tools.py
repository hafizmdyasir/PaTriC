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

from pypatric.keys import *
from pypatric.classes import *


def insertIfNotExists(dictionary: dict, key: str, value):
    '''Insert a value into the dictionary only if not present.'''
    if key not in dictionary.keys():
        dictionary[key] = value




def insertDefaults(particle: dict, fields: dict, output: dict):
    '''Check and insert defaults in the deck.'''
    
    insertIfNotExists(particle, PARTICLE_COUNT, 1)
    
    particle[MASS] = float(particle[MASS])
    particle[CHARGE] = float(particle[CHARGE])
    # If positions are provided individually for each particle, replace with the Static class.
    if isinstance(particle[INITIAL_POSITION], tuple):
        tempList = []
        for entry in particle[INITIAL_POSITION]:
            tempList.append(Static(*entry))
        particle[INITIAL_POSITION] = tuple(tempList)
    
    else:
        particle[INITIAL_POSITION] = tuple([particle[INITIAL_POSITION]])

    # If velocities are provided individually for each particle, replace with the Static class.
    if isinstance(particle[INITIAL_VELOCITY], tuple):
        tempList = []
        for entry in particle[INITIAL_VELOCITY]:
            tempList.append(Static(*entry))
        particle[INITIAL_VELOCITY] = tuple(tempList)
    
    else:
        particle[INITIAL_VELOCITY] = tuple([particle[INITIAL_VELOCITY]])
    
    
    
    insertIfNotExists(fields, E_FIELD, tuple([]))
    insertIfNotExists(fields, B_FIELD, tuple([]))


def validatePresence(control: dict, particle: dict, fields:dict, output: dict):
    '''
    Validates the input deck for required arguments. Only checks presence and not correctness.
    '''

    # Step 1: Validate control dict. All keys are required.
    given_keys = control.keys()
    required_keys = set([TIME_STEP, NUM_ITERS, INTEGRATOR, READOUT_FREQ])
    missing_keys = required_keys - set(given_keys)
    if len(missing_keys) > 0:
        raise KeyError(f'Missing control keys: {missing_keys}')
    
    # Step 2: Check particle dict.
    given_keys = particle.keys()
    if (MASS not in given_keys):
        raise KeyError(f'Missing particle key: MASS')
    
    if (CHARGE not in given_keys):
        raise KeyError(f'Missing particle key: CHARGE')

    if INITIAL_POSITION not in given_keys:
        raise KeyError(f'Missing particle keys related to initial position.')
    
    if INITIAL_VELOCITY not in given_keys:
        raise KeyError(f'Missing particle keys related to initial velocity.')


    # Step 3: Validate field dict.
    given_keys = fields.keys()
    if E_FIELD not in given_keys:
        raise KeyError(f'Missing field keys related to electric field.')
    
    if B_FIELD not in given_keys:
        raise KeyError(f'Missing field keys related to magnetic field.')
    

    # Step 4: Validate output dict.
    if FILENAME not in output.keys():
        raise KeyError(f'Missing output key: FILENAME')
    
    if DUMP_VARIABLES not in output.keys():
        raise KeyError(f'Missing output key: DUMP_VARIABLES')
    


def validateEntries(control: dict, particle: dict, fields:dict, output: dict):
    '''Validate the values entered in the dictionaries.'''

    # Step 1: Control deck
    assert isinstance(control[TIME_STEP], float) and (control[TIME_STEP] > 0)
    assert isinstance(control[NUM_ITERS], int) and (control[NUM_ITERS] > 0)
    assert isinstance(control[INTEGRATOR], int) and (BORIS <= control[INTEGRATOR] <= HIGUERA_CARY)
    assert isinstance(control[READOUT_FREQ], int)


    # Step 2: Particle deck
    assert isinstance(particle[MASS], float) and (particle[MASS] > 0)
    assert isinstance(particle[CHARGE], float) and (particle[CHARGE] > 0)
    assert isinstance(particle[PARTICLE_COUNT], int) and (particle[PARTICLE_COUNT] > 0)
    assert isinstance(particle[INITIAL_POSITION], tuple)
    assert isinstance(particle[INITIAL_VELOCITY], tuple)

    # Step 3: Field deck
    assert isinstance(fields[E_FIELD], tuple)
    assert isinstance(fields[B_FIELD], tuple)


    # Step 4: Output deck
    availableVars = (POS_X, POS_Y, POS_Z, VEL_X, VEL_Y, VEL_Z)
    for dumpVar in output[DUMP_VARIABLES]:
        if dumpVar not in availableVars:
            raise KeyError(f'Invalid dump variable: {dumpVar}')



    
