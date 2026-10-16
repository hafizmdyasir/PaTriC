---
title: Parallelization
icon: lucide/cpu
---
# Multi - Threading

The easiest way to parallelize your simulation is to use OpenMP threads. PaTriC uses OpenMP to parallelize the particle push algorithm, which is the most computationally expensive part of the simulation. This means that you can run your simulation on multiple threads and get a significant speedup.

This is achieved by setting the environment variable `OMP_NUM_THREADS` to the number of threads you want to use. For example, to run your simulation on 4 threads, you can do the following:

```bash
export OMP_NUM_THREADS=4
patric input.cpp
```

Doing so will divide the particles among the threads and each thread will push its own set of particles. This is a simple and effective way to parallelize your simulation, but it does have some limitations. For example, if you have a small number of particles, then the overhead of creating and managing threads may outweigh the benefits of parallelization.

!!! tip "Thread Count"
    Continuously increasing the number of threads will not necessarily yield maximum performance. The optimal number of threads depends on the number of particles as well as your CPU. You can use the command `lscpu` to see the number of cores available on your machine.

# MPI Parallelization
!!! note "In Development"
    MPI parallelization is currently under development and will be available in a future release. This will allow you to run your simulation on multiple nodes and get even more speedup. Stay tuned!

The optimal MPI parallelization depends on the node/core configuration you are able to access. Typically, it is best to set the number of MPI processes to the number of sockets you have access to, and use the remaining cores for OpenMP threads. Do remember that these are suggestions and you can always experiment with different configurations to see what works best for your simulation.

!!! example "2 Sockets, 16 Cores"
    If you have access to a node with 2 sockets and 16 cores, then you can run your simulation on 2 MPI processes and use 8 OpenMP threads per process. This should give you the best performance.
    ```bash
    export OMP_NUM_THREADS=8
    mpirun -np 2 patric input.cpp
    ```
