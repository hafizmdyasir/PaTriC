---
title: Units
icon: lucide/scale
---

# Units

## Basic Quantities
The electron serves as our basis of normalization in PaTriC, where charge, mass, and velocity are normalized with respect to the electron charge, mass, and speed of light, respectively. This means that the charge of an electron is -1, its mass is 1, and the speed of light is also 1. A few derived quantities can then be defined:

* Energy \(E_r = m_ec^2\)
* Momentum \(p_r = m_ec\)
* Temperature \(T_r = m_ec^2\)

## Reference Quantities
This alone is not sufficient for defining a complete system of units and for that purpose, one can select a reference frequency \(\omega_r\). Together with \(q\), \(m_e\), and \(c\), we can define a complete system of units. More often than not, it is convenient to select the reference frequency as the angular frequency of a known physical system.

For instance, if \(\omega_r\) is chosen as the angular frequency of electron in a uniform magnetic field of 1 Tesla, then the remaining quantities can be defined as follows:

| Quantity                         | Formula              | SI Units                                  |
| -------------------------------- | -------------------- | ----------------------------------------- |
| \(\omega_r\) (Angular Frequency) | \(qB/m_e\)           | \(1.75 \times 10^{11}\) rad . s \(^{-1}\) |
| \(T_r\) (Time)                   | \(1 / \omega_r\)     | \(5.6875\) ps                             |
| \(L_r\) (Length)                 | \(c / \omega_r\)     | \(1.70625\) mm                            |
| \(E_r\) (Electric Field)         | \(m_ec\omega_r/q\)   | \(3 \times 10^8\) V/m                     |
| \(B_r\) (Magnetic Field)         | \(m_e \omega_r / q\) | \(1\) Tesla                               |


## SI Units
You can also choose to use SI units in PaTriC. In this case, the compilation process changes slightly. Provide the parameter `SI_UNITS=true` to the makefile while doing `make` and it will take care of the rest. 