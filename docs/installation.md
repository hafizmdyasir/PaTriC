---
title: Getting Started
icon: lucide/download
---

The installation process has a few simple steps:

## Get the prerequisites
You will need:

1. A C++ compiler that supports OpenMP. Most Linux systems ship with one by default, and you are free to choose whichever you find most suitable. 
2. An implementation of Make: The GNU Make that ships with most systems should suffice.

## Get the code
Clone the PaTriC repository into a folder of your choice:

``` bash
git clone https://github.com/hafizmdyasir/PaTriC.git
```

## Compile and install
PaTriC's makefile expects the environment variables `CXX` and `PREFIX` to be defined and point to your C++ compiler binary and your preferred install location, respectively. The typical installation procedure looks like this:

```bash
cd patric
export CXX=g++
export PREFIX=/usr/local        # Requires sudo. Alternatively, install into $HOME/.local
make; make install
```

!!! info
    By default, `make` will attempt to install into `/usr/local` and use `g++` for compilation. You can override this by setting the environment variables `CXX` and `PREFIX`. Make sure to update the `CXXFLAGS` in the makefile accordingly.

### Compilation Flags
You can use the following parameters to control the compilation process:

1. `SI_UNITS`: Do `make SI_UNITS=true` and PaTriC will use SI units for its calculations instead of normalized ones (see [Units](units.md)).
2. `HIGH_PRECISION/LOW_PRECISION`: If either of these flags are set to true, then the calculation precision will be altered. `HIGH_PRECISION` corresponds to `long double`, while `LOW_PRECISION` corresponds to `float`. By default, `double` is used. Note that this behaviour is machine-dependent.
3. `DEBUG`: For developers, this adds the flags `-g -O0` to `CXXFLAGS`, allowing for easier debugging.


## Run
Open a terminal window and type `patric`. If everything has happened correctly, you should get the following output:
``` { .yaml .no-copy .no-select}
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

No configuration file specified. Program will exit.
```

In practice, you will need to provide the input script (see [Input](input.md)) as an argument to the program. You can also choose to run it with multiple threads or via `mpirun` (see [Parallelization](parallelize.md)).