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
Classes that represent various types of electric and magnetic field geometries. 
Serves as the base file and more geometries are defined in files electric.py and magnetic.py
'''





from typing import Literal

variablesDictionary = {'T': 0, 'X': 1, 'Y': 2, 'Z': 3}  



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
        return "Uniform" + f"{self.minimum[0], self.minimum[1], self.minimum[2], self.maximum[0], self.maximum[1], self.maximum[2]}"
    
    def __repr__(self) -> str:
        return self.__str__()



class Maxwellian:
    '''
    Represents a random velocity distribution that is maxwellian in nature.
    '''
    def __init__(self, temperature: tuple[float, float, float]):
        '''
        Parameters
        ----------
        temperature : tuple
            Temperature of the velocity distribution in Kelvins. The entries in this tuple correspond to the temperatures for x, y, and z directions, respectively.
        '''
        self.temperature = temperature
    

    def __str__(self) -> str:
        return f'Maxwellian{self.temperature[0], self.temperature[1], self.temperature[2]}'
    
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


class SinField:
    '''
    Represents an electric/magnetic field that varies sinusodially in either time, x, y, or z. 
    That is, the field will be calculated as f = sin(omega*variable + phi)
    '''
    def __init__(self, variable: Literal['X', 'Y', 'Z', 'T'], omega: float, phi: float = 0):
        '''
        Parameters
        ----------
        variable: The variable in which, the field varies.
        omega: The angular frequency of the field.
        phi: The phase of the field (if any).
        '''  
        self.variable = variablesDictionary[variable]
        self.omega = omega
        self.phi = phi

    def __str__(self) -> str:
        return f'SinField({self.variable}, {self.omega}, {self.phi})'
    
    def __repr__(self) -> str:
        return self.__str__()
    

class GaussField:
    '''
    Represents a gaussian field in either time, x, y, or z.
    The field will be calculated as f = a * exp( ((variable-b) / c)**m)
    The default value for m is 2. Support is provided for other powers.
    '''
    def __init__(self, variable: Literal['X', 'Y', 'Z', 'T'], a: float, b: float, c: float, m: float = 2):
        '''
        Parameters
        ----------
        variable: The variable in which, the field varies.
        a: The amplitude of the field.
        b: The mean of the field.
        c: The standard deviation of the field.
        m: Optional parameter to provide support for Super Gauss functions.
        '''
        self.variable = variablesDictionary[variable]
        self.a = a
        self.b = b
        self.c = c
        self.m = m

    def __str__(self) -> str:
        return f'GaussField({self.variable}, {self.a}, {self.b}, {self.c}, {self.m})'
    
    def __repr__(self) -> str:
        return self.__str__()