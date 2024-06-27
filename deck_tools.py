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
    __insertIfNotExists(output, FILE_HEADER, tuple([]))

    if (len(output[FILEPATH]) > 0) and not str(output[FILEPATH]).endswith('/'):
        output[FILEPATH] = output[FILEPATH] + '/'



def validatePresence(control: dict, particle: dict, fields:dict, output: dict):
    '''
    Validates the input deck for required arguments. Only checks presence and not correctness.
    '''

    # Step 1: Validate control dict. All keys are required.
    given_keys = control.keys()
    if TIME_STEP not in given_keys:
        raise KeyError(f'Missing control key: TIME_STEP')
    
    if NUM_ITERS not in given_keys:
        raise KeyError(f'Missing control keu: NUM_ITERS')
    
    if INTEGRATOR not in given_keys:
        raise KeyError(f'Missing control key: INTEGRATOR')
    
    if READOUT_FREQ not in given_keys:
        raise KeyError(f'Missing control key: READOUT_FREQ')
    
    # Step 2: Check particle dict.
    given_keys = particle.keys()
    if MASS not in given_keys:
        raise KeyError(f'Missing particle key: MASS')
    
    if CHARGE not in given_keys:
        raise KeyError(f'Missing particle key: CHARGE')
    
    if PARTICLE_COUNT not in given_keys:
        raise KeyError(f'Missing particle key: PARTICLE_COUNT')

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
    
    if FILEPATH not in output.keys():
        raise KeyError(f'Missing output key: FILEPATH')
    
    if FILE_HEADER not in output.keys():
        raise KeyError(f'Missing output key: FILE_HEADER')
    
    if DUMP_VARIABLES not in output.keys():
        raise KeyError(f'Missing output key: DUMP_VARIABLES')
    


def validateEntries(control: dict, particle: dict, fields:dict, output: dict):
    '''Validate the values entered in the dictionaries.'''

    # Step 1: Control deck
    if not isinstance(control[TIME_STEP], float) or control[TIME_STEP] <= 0:
        raise KeyError(f'Invalid TIME_STEP: {control[TIME_STEP]} - Must be a positive float.')
    
    if not isinstance(control[NUM_ITERS], int) or control[NUM_ITERS] <= 0:
        raise KeyError(f'Invalid NUM_ITERS: {control[NUM_ITERS]} - Must be a positive integer.')
    
    if not isinstance(control[INTEGRATOR], int) or not (BORIS <= control[INTEGRATOR] <= HIGUERA_CARY):
        raise KeyError(f'Invalid INTEGRATOR: {control[INTEGRATOR]} - Must be one of (BORIS, VAY, HIGUERA_CARY).')
    
    if not isinstance(control[READOUT_FREQ], int):
        raise KeyError(f'Invalid READOUT_FREQ: {control[READOUT_FREQ]} - Must be an integer.')
    
    
    # Step 2: Particle deck
    if not isinstance(particle[MASS], float) or particle[MASS] <= 0:
        raise KeyError(f'Invalid MASS: {particle[MASS]} - Must be a positive float.')
    
    if not isinstance(particle[CHARGE], float):
        raise KeyError(f'Invalid CHARGE: {particle[CHARGE]} - Must be a float.')
    
    if not isinstance(particle[PARTICLE_COUNT], int) or particle[PARTICLE_COUNT] <= 0:
        raise KeyError(f'Invalid PARTICLE_COUNT: {particle[PARTICLE_COUNT]} - Must be a positive integer.')
    
    if not isinstance(particle[INITIAL_POSITION], tuple):
        raise KeyError(f'Invalid INITIAL_POSITION: {particle[INITIAL_POSITION]} - Must be a tuple.')
    else:
        if type(particle[INITIAL_POSITION][0]) not in [Static, Uniform, Random]:
            raise KeyError(f'Invalid INITIAL_POSITION. Expected either of (Static, Uniform, Random).')
    
    if not isinstance(particle[INITIAL_VELOCITY], tuple):
        raise KeyError(f'Invalid INITIAL_VELOCITY: {particle[INITIAL_VELOCITY]} - Must be a tuple.')
    elif type(particle[INITIAL_VELOCITY][0]) not in [Static, Uniform, Maxwellian]:
            raise KeyError(f'Invalid INITIAL_VELOCITY. Expected either of (Static, Uniform, Maxwellian).')
    
    
    # Step 3: Field deck
    if not isinstance(fields[E_FIELD], tuple) and not callable(fields[E_FIELD]):
        raise KeyError(f'Invalid E_FIELD: {fields[E_FIELD]} - Must be a tuple or a function.')
    
    if not isinstance(fields[B_FIELD], tuple) and not callable(fields[B_FIELD]):
        raise KeyError(f'Invalid B_FIELD: {fields[B_FIELD]} - Must be a tuple or a function.')
    


    # Step 4: Output deck
    availableVars = (POS_X, POS_Y, POS_Z, VEL_X, VEL_Y, VEL_Z, GAMMA, E_FIELD_X, E_FIELD_Y, E_FIELD_Z, B_FIELD_X, B_FIELD_Y, B_FIELD_Z)
    for dumpVar in output[DUMP_VARIABLES]:
        if dumpVar not in availableVars:
            raise KeyError(f'Invalid dump variable: {dumpVar}')



    
