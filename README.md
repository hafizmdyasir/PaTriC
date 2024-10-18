# PaTriC - Particle Tracker in C++
> By Mohammad Yasir

## About PaTriC
**PaTriC** is an open-source, user-friendly, fully relativistic charged particle tracking code that can simulate the motion of any number of particles in certain electric and magnetic fields. Learn more at the [Official Documentation](https://hafizmdyasir.github.io/patric-user-manual/)

PaTriC utilizes the particle orbit theory and ignores inter-particle interactions, making it suitable for simulating the expected behaviour of plasma particles by showcasing how isolated particles will behave.

## Code Structure
The core components of PaTriC are written entirely in C++, and are broken into several header files for ease of understanding. The entry point of the application is in `main.cpp`. 

To run the program, take the following steps:
1. Compile all headers.
2. Compile all source files.
3. Write the input deck, which is declared in Python.
4. Run the program using terminal and provide the path to the input deck as an argument.

## Plotting Output
The data from simulation runs is dumped into plain text `.dat` files, which can be opened via any software of your choice and easily plotted with any plotting tool.

For the users' convenience, PaTriC ships with its own plotting utilities that are written in python.

## Acknowledgements
PaTriC has been developed under the supervision of Professor Dr. Vikrant Saxena at the Indian Institute of Technology, Delhi. The authors would like to acknowledge his contributions and interest in the program. Further, the authors acknowledge the central role that the institute has played in providing the resources and the means for PaTriC to see the light of day.