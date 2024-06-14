'''
UTILITIES.py
============
Created: 31.05.2024

Copyright 
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Common utility functions
'''

from numpy import loadtxt
import argparse


def extractVariables():
    # Load data from .dat file
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--file", type=str)
    args = parser.parse_args()

    filename = args.file

    t, x, y, z = loadtxt(filename, unpack=True)
    return t, x, y, z