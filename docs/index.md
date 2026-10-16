---
title: Particle Tracker in C++
icon: lucide/home
---

# Particle Tracker in C++

``` {.yaml .no-copy .no-select}
 ####        #######                 ####   
#    #          #                   #    #  
#    #          #                   #       
#####   ###     #     ###   #####   #       
#      #   #    #    #   #    #     #       
#      #####    #    ####     #     #    #  
#      #   #    #    #   #  #####    ####   
__________________________________________
Particle Tracker in C++
Version 2.0.0

By Mohammad Yasir
IIT Delhi
```

PaTriC is an **open-source**, **fully relativistic**, **multi-threaded** charged particle tracker with support for arbitrary electric and magnetic fields. It utilizes the isolated particle model and thus, can simulate the motion of any number of charges in a given field configuration. All you need is a C++ compiler and PaTriC is yours to play with.

PaTriC is designed to be highly flexible and easy to use, allowing users to customize every aspect of the simulation and output. When you set up the simulation, you instruct PaTriC about the time-step, the integrator, the number of particles, the electromagnetic fields, and the data to output. PaTriC uses the specified integration algorithm to solve the equation of motion for the target particles using the Lorentz Force as the driving force. It then saves the variables you requested to simple, human-readable output files.


# Features
* **Fully relativistic**: The particle push algorithms available in PaTriC take the relativistic factor (gamma) into consideration while calculating the velocity updates. By default, the Boris push is used.
* **Multi-threading**: By using OpenMP threads, PaTriC can track a large number of particles all at once, making it extremely suitable for nodes with large core counts.
* **Open-source**: The entire codebase is available on [GitHub](https://www.github.com/hafizmdyasir/PaTriC) under the Apache 2.0 Licence.


# Download

[:fontawesome-brands-github: Download from GitHub](https://github.com/hafizmdyasir/PaTriC/archive/refs/heads/main.zip){ .md-button .md-button--primary }