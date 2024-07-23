'''
PY_PARSER.py
============
Created: 17.05.2024

Copyright
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Script to open the input file and do what needs be done. 
'''


from importlib.util import spec_from_file_location, module_from_spec
from os import makedirs
import argparse

from pypatric.keys import *
from deck_tools import *




def getFilePath():
    '''Get file path from arguments.'''
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", type=str)
    args = parser.parse_args()
    return args.file


def import_file(path):
    '''Try to import all attributes from the deck in here.'''

    # Load the module from the file path
    spec = spec_from_file_location("module", path)
    module = module_from_spec(spec)                     #type:ignore
    spec.loader.exec_module(module)                     #type:ignore
    
    # Import all attributes from the module into the current namespace
    globals().update(vars(module))


def writeToTemp():

    makedirs('temp', exist_ok=True)
    with open('temp/config.dmp', 'w') as tempFile:
        
        tempFile.write("# CONTROL DICT\n")
        for (key, value) in Control.items():  # type: ignore
            tempFile.write(f"{key}: {value}\n")

        tempFile.write("\n# PARTICLE DICT\n")
        for (key, value) in Particle.items(): # type: ignore
            tempFile.write(f"{key}: {value}\n")

        tempFile.write("\n# FIELDS DICT\n")
        for (key, value) in Fields.items():   # type: ignore
            if callable(value):
                tempFile.write(f"{key}: {value.__name__}\n")
                continue
            tempFile.write(f"{key}: {value}\n")

        tempFile.write("\n# OUTPUT DICT\n")
        for (key, value) in Output.items(): # type: ignore
            tempFile.write(f"{key}: {value}\n")


# First, open file, get all attributes, and write them to temp.
pat = getFilePath()
import_file(pat)
insertDefaults(Control, Particle, Fields, Output)#type:ignore
writeToTemp()