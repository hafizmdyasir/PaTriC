---
title: The Input File
icon: lucide/code
---

# Structure
PaTriC uses C++ to setup your simulation. Example `input.cpp` and various benchmark files ship with the repository that you can copy and adjust for your use case.

When the program starts, it compiles the input file provided using the *same* compiler and compiler flags that were used to compile PaTriC itself. The input file must include the header `patric.h` that is installed with the program binary when you do `make install`.

The program then looks for a function called `configureSimulation` in the input file and calls it to set up the parameters of the simulation. This function takes various arguments, which are explained in the following sections. Overall, the function looks like so:
```cpp
void configureSimulation(Control*& ctrl, Particle*& prtcl, Fields*& fields, Output*& output) {
    // do stuff you need, define variables etc.
    ctrl   = new Control(timestep, simulationTime, particlePusher);
    prtcl  = new Particle(count, charge, mass, initialPositions, initialVelocities);
    fields = new Fields(electricFieldFunction, magneticFieldFunction);
    output = new Output(outputFileName, outputFilePath, outputFrequency, outputVariables);
}
```


## Control
The Control class contains information relevant to the setup of the simulation itself. This includes just three things:

1. `timestep`: the time-step used by the integration algorithm.
2. `simulationTime`: time till which the simulation will run for.
3. `particlePusher`: the particle push algorithm to use. This must be either of `Pusher::Boris` [[2]](#reference-boris), `Pusher::Vay` [[3]](#reference-vay), or `Pusher::HigueraCary` [[4]](#reference-hig). A comparison of each of these algorithms is given in reference [[1]](#reference-integrator).

With the above variables, the control object is then initialized like so:
```cpp
ctrl = new Control(0.001, 1000, Pusher::Boris);
```

## Particle
This is a simple container for the target information. This includes:

1. `count`: the number of particles to load and simulate.
2. `charge`: the charge of the particle (in units of electron charge, see [Units](units.md)).
3. `mass`: the mass of the particle (again in units of electron mass).
4. `initialPositions`: the initial position of each of the particles.
5. `initialVelocities`: the initial velocities of each of the particles.

### Loading Initial Conditions
The `Particle()` constructor expects `std::vectors` of `Vector3D` objects for the `initialPositions` and `initialVelocities`. For example, initialising a single particle at the origin with zero velocity looks like this:
```cpp
prtcl = new Particle(1, -1, 1, {Vector3D(0, 0, 0)}, {Vector3D(0, 0, 0)});
```

For a large number of particles, creating the vectors manually becomes cumbersome. The PaTriC header `patric.h` provides a few helpful functions to tackle this. They are outlined below:

#### `getSameIC()`
Returns a vector containg the same values for all particles, which is to be provided as a `Vector3D` object. For example, to initialise 10 particles at the same position and velocity, you can do the following:

```cpp
int particleCount = 10;
int particleCharge = -1.0;
int particleMass = 1.0;
prtcl = new Particle(particleCount, particleCharge, particleMass, 
        //x,y,z are the position coordinates.
        getSameIC(particleCount, Vector3D(x,y,z)),      
        // vx,vy,vz are the velocity components.
        getSameIC(particleCount, Vector3D(vx, vy, vz))  
    );
```


#### `getRandomIC()`
Returns a vector of initial conditions, where each component has been randomly drawn from a uniform distribution between the provided limits.

```cpp
prtcl = new Particle(particleCount, particleCharge, particleMass, 
        // Each particle gets a random position with components between the provided values.
        getRandomIC(particleCount, xmin, xmax, ymin, ymax, zmin, zmax),             
        // For either of the directions, if upper and lower values are equal, the same value is assigned.
        getRandomIC(particleCount, vx_min, vx_max, vy_min, vy_max, vz_min, vz_max) 
    );      
```


#### `getRegularIC()`
Returns a vector where each component has been uniformly distributed between the provided limits. 

```cpp
prtcl = new Particle(particleCount, particleCharge, particleMass, 
        getRegularIC(particleCount, xmin, xmax, ymin, ymax, zmin, zmax),            
        getRegularIC(particleCount, vx_min, vx_max, vy_min, vy_max, vz_min, vz_max) 
    );  // Particles are spread evenly across the three-dimensional space.
```

#### `getMaxwellianIC()`
It is also possible to get a vector of values that are spread with a given temperature. This depends on the particle mass and a Box-Muller transform is used to return thermally spread values centered on 0.
```cpp
std::vector<Vector3D> thermalSpread = getMaxwellianIC(particleCount, temperature, particleMass);
```
## Fields
The choice of the electric and magnetic fields is entirely arbitrary. They can be left blank to simulate the individual motion of each particle on its own. Once again, the following helpful functions from `patric.h` will be useful for this purpose. Each of these returns an `std::function` object that takes two arguments: the position at which to calculate the field, and the time at which to calculate it. The function returns the electric/magnetic field calculated at the provided location at the provided time. The object is initialized as:
```cpp
fields = new Fields(electricFieldFunction, magneticFieldFunction);
```

!!! info
    For the ease of programming, this function is defined as a `FieldGetter` type in the header file. It is defined as `typedef std::function<Vector3D(Vector3D, real)> FieldGetter;`

    Thus, each of the following inbuilt function returns an object of type `FieldGetter`.

### Inbuilt Fields
The following helper functions may be used to setup the fields.

#### `getConstantField()`
Creates a function that returns the same, constant field everywhere at every time-step. Provide the value of this field into the argument as a `Vector3D` object. 

#### `getSineField()`
This functions takes the arguments \( (A, \omega, \phi, v, \hat{u})\) and returns a `FieldGetter` that calculates the field as:

\[
\vec{E} = A \sin (\omega \cdot v + \phi)\ \hat{u}
\]

Here, 

* A: amplitude of field.
* \(\omega\): angular frequency
* v: the field is sinusoidal in this variable. Must be one of `T, X, Y,` or `Z`
* \(\phi\): extra phase
* \(\hat{u}\): unit vector along which, the field points.

#### `getGaussianField()`
Takes the arguments \((A, \sigma, \mu, m, v, \hat{u})\) and returns a function that drives a gaussian/super-gaussian field using the formula:

\[
\vec{E} = A \exp (-(v-\mu)^m / 2\sigma^m)\ \hat{u}
\]

Here, A, u, and v are same as before and

* \(\mu\): the exponent for the gaussian
* \(\sigma\): the standard deviation


### Custom Fields
If you want to define your own field, you can use the inbuilt `FieldGetter` type definition. It is created as follows:
```cpp
FieldGetter myCustomField = [](Vector3D position, real time) {
    // some work
    return Vector3D(x_component, y_component, z_component);
};
```


## Output
The output object contains information required to store the results of your simulation. Each particle gets its own file numbered from 0 through `particleCount-1`. Data is stored in tab-separated, human-readable `.dat` files. You can choose to provide a custom path for these files. The object is initialized as follows:

```cpp
string outputFileName = "output";
string outputFilePath = "./data/";
unsigned int outputFrequency = 20;
vector<string> outputVariables = {POS_X, POS_Y, POS_Z, VEL_X, VEL_Y, VEL_Z};
output = new Output(outputFileName, outputFilePath, outputFrequency, outputVariables);
```

The first three arguments are self-explanatory. The program dumps the information requested via `outputVariables` vector (discussed below) at every `outputFrequency`-th iteration. To select which variables are dumped into the file, you can make use of pre-defined constants, which are listed below:

* `POS_X`: particle's position - x component
* `POS_Y`: particle's position - y component
* `POS_Z`: particle's position - z component
* `VEL_X`: particle's velocity - x component
* `VEL_Y`: particle's velocity - y component
* `VEL_Z`: particle's velocity - z component
* `GAMMA`: particle's relativistic factor, calculated as \(\gamma = \sqrt{1 / (1 - (v/c)^2)}\)
* `E_FIELD_X`: electric field experienced by the particle at that time-step - x component
* `E_FIELD_Y`: electric field experienced by the particle at that time-step - y component
* `E_FIELD_Z`: electric field experienced by the particle at that time-step - z component
* `B_FIELD_X`: magnetic field experienced by the particle at that time-step - x component
* `B_FIELD_Y`: magnetic field experienced by the particle at that time-step - y component
* `B_FIELD_Z`: magnetic field experienced by the particle at that time-step - z component


# References
1. M. Yasir and V. Saxena 2025 Phys. Scr. 100 015605, doi: <a id=reference-integrator href="https://www.doi.org/10.1088/1402-4896/ad98c2" target=_blank>10.1088/1402-4896/ad98c2</a>
2. Boris, Jay P. 1970 Proc. Fourth Conf. Num. Sim. Plasmas. Link: <a id=reference-boris href=https://www.google.co.in/books/edition/Proceedings_Fourth_Conference_on_Numeric/BrSraqqVxU8C?hl=en>Google Books</a> 
3. J.-L. Vay. 2008 Physics of Plasmas, 15(5):056701, 02, doi: <a id=reference-vay href=https://doi.org/10.1063/1.2837054>10.1063/1.2837054</a>
4. A. Higuera and J. R. Cary 2017 IEEE International Conference on Plasma Science (ICOPS), pages 1–1, doi: <a id=reference-hig href=https://doi.org/10.1109/ICOPS36557.2017>10.1109/ICOPS36557.2017</a>