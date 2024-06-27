'''
PYSERVER.py
===========
Created: 27.06.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
This script is called from the PythonServer declared in .cpp. It stores custom functions etc.
'''


from importlib.util import spec_from_file_location, module_from_spec
from pydoc import importfile
import argparse, sys


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


if __name__ == "__main__":
    import_file(getFilePath())
    while True:
        line = sys.stdin.readline().strip()
        if not line:
            break
        parts = line.split()
        function_name = parts[0]
        args = list(map(float, parts[1:]))
        
        if function_name in globals().keys():
            results = globals()[function_name](*args)
            print(f"{results[0]} {results[1]} {results[2]}")
            sys.stdout.flush()
        else:
            raise KeyError(f'It looks like you didn\'t pass the correct function name. {function_name}(x,y,z, t) is not defined.')
