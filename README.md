# Ansys-Fluent-Gray-Scott-
Simulation of Turing instability using Ansys fluent

## How To Set this up in Ansys Student 2025
1. Create new Ansys Fluent project
2. Head up straight to Setup cell and open it
3. Import file Setup.cas.h5 using Case import in Fluent. Setup.cas.h5 file contains information about mesh and all solver settings that are needed to solve the Reaction-Diffusion system for 2 scalars.
4. Head to User-Defined tab and add gray_scott.c file as compiled build using libudf and load. Check if udf_init is present in function hooks tab.
5. Initialize the initial conditions and use contours of u or v(in Results tab on the left side) to verify whether the initialization is correct.
6. If everything is correct go to calculation set time step size and amount of steps(in solution tab on the left side).
7. Press calculate and watch pattern creation. (Currently animation is set to update every 10 time steps as it is quite memory consuming if you want change it go to Calculation Activities and edit v-animation)


## What is Turing instability?
Turing instability is a biological phenomenon that can be explored in systems of reaction-diffusion equations. You can read more about it in my 2024 conference poster (in Polish) below:
[Poster Poznań 2024](imgfiles/poster.pdf)
(Simulations in the poster were made using different methods from those used here)
In short, this phenomenon occurs when a system is stable without diffusion but becomes unstable when diffusion is included. For certain sets of parameters, it leads to the formation of spatial patterns.

This model can reproduce patterns similar to those observed on animal skin or fur. For some parameters, the resulting patterns clearly resemble those naturally occurring on animal coats.


## Some pictures
![Pattern for F=0.038, K-0.061](imgfiles/gs3861.png)
<img src="imgfiles/gs3861.png" alt="Pattern formation" width="400">
