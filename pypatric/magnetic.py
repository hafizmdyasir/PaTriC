'''
MAGNETIC.py
===========
Created: 18.06.2024

Copyright
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Contains classes that describe magnetic field geometries
'''


# The static class is already defined for positions and velocities. 
# We just need it here to make the file complete.
from classes import Static, SinField, GaussField


class Wire:
    '''
    Represents a wire of finite or infinite length placed at a finite distance from the origin.'''

    def __init__(self, current: float, length: float, position: tuple[float, float, float], direction: int):
        '''
        Parameters
        ----------
        current : Current flowing through the wire.
        length : Length of the wire.
        position : Position of the wire's midpoint.
        direction : angles made by x, y, and z axes respectively, in radians.
        '''
        self.length = length
        self.current = current
        self.position = position
        self.direction = direction
    

    def __str__(self) -> str:
        return f"Wire({self.current}, {self.length}, {self.position[0]}, {self.position[1]}, {self.position[2]}, {self.direction})"
    
    def __repr__(self) -> str:
        return self.__str__()


class Coil:
    '''
    Represents a coil of given radius, carrying a certain current, placed at a point along the z-axis. No other axis is supported at the moment.
    '''
    def __init__(self, radius: float, current: float, zPosition: float = 0):
        '''
        Parameters
        ----------
        radius : float Radius of the coil.
        current : float Current flowing through the coil. It is redundant to include number of turns since that can easily be incorporated by multiplying the current with the number of turns.
        zPosition : float Position of the coil along the z-axis.
        '''
        self.radius = radius
        self.current = current
        self.zPosition = zPosition

    def __str__(self) -> str:
        return f"Coil({self.radius}, {self.current}, {self.zPosition})"
    
    def __repr__(self) -> str:
        return self.__str__()