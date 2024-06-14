'''
CLASSES.py
==========
Created: 03.06.2024

Copyright
Mohammad Yasir
Research Scholar, IIT-D

All rights reserved. No part of this code may be used, modified, shared, or reproduced in any form without express permission of its author.

DESCRIPTION
-----------
Classes that represent various types of electric and magnetic field geometries. Also includes options for declaring particle positions and velocities.
'''


class Random:
    '''
    Represents a random distribution between minimum and maximum.
    '''
    def __init__(self, minimum: tuple[float, float, float], maximum: tuple[float, float, float]):
        '''
        Parameters
        ----------
        minimum : tuple[float, float, float]
            Minimum x, y, and z coordinates of the random position.
        maximum : tuple[float, float, float]
            Maximum x, y, and z coordinates of the random position.
        '''
        self.minimum = minimum
        self.maximum = maximum
    

    def __str__(self) -> str:
        return f"Random{*self.minimum, *self.maximum}"

    def __repr__(self) -> str:
        return self.__str__()



class Uniform:
    '''
    Represents uniform setter.
    '''
    def __init__(self, minimum: tuple[float, float, float], maximum: tuple[float, float, float]):
        '''
        Parameters
        ----------
        minimum : tuple[float, float, float]
            Minimum x, y, and z coordinates of the uniform position.
        maximum : tuple[float, float, float]
            Maximum x, y, and z coordinates of the uniform position.
        '''
        self.minimum = minimum
        self.maximum = maximum
    

    def __str__(self) -> str:
        return "Uniform" + f"({self.minimum[0], self.minimum[1], self.minimum[2], self.maximum[0], self.maximum[1], self.maximum[2]})"
    
    def __repr__(self) -> str:
        return self.__str__()



class Maxwellian:
    '''
    Represents a random velocity distribution that is maxwellian in nature.
    '''
    def __init__(self, temperature: float):
        '''
        Parameters
        ----------
        temperature : float
            Temperature of the velocity distribution in Kelvins.
        '''
        self.temperature = temperature
    

    def __str__(self) -> str:
        return "Maxwellian" + f"({self.temperature})"
    
    def __repr__(self) -> str:
        return self.__str__()


class Static:
    '''
    Represents a constant, static value.
    '''
    def __init__(self, x, y, z):
        '''
        Parameters
        ----------
        x : float x-component of the magnetic field.
        y : float y-component of the magnetic field.
        z : float z-component of the magnetic field.
        '''
        self.x = x
        self.y = y
        self.z = z
    

    def __str__(self) -> str:
        return f"Static({self.x}, {self.y}, {self.z})"
    
    def __repr__(self) -> str:
        return self.__str__()



class Wire:
    '''
    Represents a wire of finite or infinite length placed at a finite distance from the origin.'''

    def __init__(self, current: float, length: float, position: tuple[float, float, float], direction: int):
        '''
        Parameters
        ----------
        current : float Current flowing through the wire.
        length : float Length of the wire.
        position : tuple Position of the wire's midpoint.
        direction : tuple angles made by x, y, and z axes respectively, in radians.
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