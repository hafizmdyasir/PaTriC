# PaTriC - Particle Tracker in C++
> By Mohammad Yasir

## About PaTriC
**PaTriC** is an open-source, user-friendly, fully relativistic charged particle tracking code that can simulate the motion of any number of particles in arbitrary electric and magnetic fields. Learn more at the [Official Documentation](https://hafizmdyasir.github.io/PaTriC/)

PaTriC ignores inter-particle interactions, making it suitable for simulating the expected behaviour of plasma particles by showcasing how isolated particles will behave. The particle update is multi-threaded, making the performance blazingly fast on modern HPC systems.

## Code Structure
The core components of PaTriC are written entirely in C++ and the input script is also provided in C++. The program stores the compiler and flags that were used to compile it and reuses them to compile the input script into a shared library. This maximizes speed and safety and reduces chances of incorrect input.

A simple `make PREFIX=/your/desired/install/location` command will take care of the compilation for you and install core libraries, include files and the executable into `$PREFIX`. You can then run it from anywhere using `patric input_file.cpp` as long as `PREFIX` is added to path.

Example input scripts are provided in the `benchmarks` folder. Copy them and you're ready to go.

## Plotting Output
The data from simulation runs is dumped into plain text `.dat` files, which can be opened via any software of your choice and easily plotted with any plotting tool.

## Acknowledgements
PaTriC has been developed under the supervision of Professor Dr. Vikrant Saxena at the Indian Institute of Technology, Delhi. The authors would like to acknowledge his contributions and interest in the program. Further, the authors acknowledge the central role that the institute has played in providing the resources and the means for PaTriC to see the light of day.
