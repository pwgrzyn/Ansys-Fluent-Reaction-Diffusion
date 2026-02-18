# Ansys-Fluent-Reaction-Diffusion
Simulation of Turing instability using Ansys fluent on a Square(where left and right border are connected and upper and lower aswell)

## How To Set this up in Ansys Student 2025
1. Create new Ansys Fluent project
2. Straight up open Setup
3. Import file Setup.cas.h5 using Case import in Fluent. Setup.cas.h5 file contains information about mesh and all solver settings that are needed to solve the Reaction-Diffusion system for 2 scalars.
4. Head to User-Defined tab and add gray_scott.c file as compiled build using libudf and load. Check if udf_init is present in function hooks tab.
5. Initialize the initial conditions and use contours of u or v(in Results tab on the left side) to verify whether the initialization is correct.
6. If everything is correct go to calculation, set time step size and amount of steps(in solution tab on the left side).
7. Press calculate and watch pattern creation. (Currently animation is set to update every 10 time steps as it is quite memory consuming if you want to change it go to Calculation Activities and edit v-animation or create your own)

## Gray-Scott Model
Gray-Scott Model is a system of two partial differential equations i.e reaction-diffusion equations of the form:

$$
\begin{aligned}
\frac{\partial u}{\partial t} &= D_u \nabla^2 u - uv^2 + F(1-u) \\
\frac{\partial v}{\partial t} &= D_v \nabla^2 v + uv^2 - (F+k)v
\end{aligned}
$$

## What is Turing instability?
Turing instability is a biological phenomenon that can be explored in systems of reaction-diffusion equations. You can read more about it and Gray-Scott model in my 2024 conference poster (in Polish) below:
[Poster Poznań 2024](imgfiles/poster.pdf)
(Simulations in the poster were made using different methods from those used here)
In short, this phenomenon occurs when a system is stable without diffusion but becomes unstable when diffusion is included. For certain sets of parameters, it leads to the formation of spatial patterns.

This model can reproduce patterns similar to those observed on animal skin or fur. For some parameters, the resulting patterns clearly resemble those naturally occurring on animal coats.


## Simulation Results
<img src="imgfiles/gs3861.png" alt="Pattern formation" width="400"> **Parameters:** F = 0.038, K = 0.061 <img src="imgfiles/gs5562.png" alt="Pattern formation" width="400"> **Parameters:** F = 0.055, K = 0.062
<img src="imgfiles/u46gs594.png" alt="Pattern formation2" width="400"> **Parameters:** F = 0.046, K = 0.0594
<img src="imgfiles/gs6261.png" alt="Pattern formation3" width="400"> **Parameters:** F = 0.062, K = 0.061


These pictures were taken when the system was almost stabilized.
Changes in the patterns were minimal, which is the desirable effect. Most of the pattern formation on skin or fur occurs during embryo development, and later changes are very small. The initial conditions for those pictures were different. For very non symmetric patterns i suggest setting the v-substance concentration at random. Also it is worth noticing that often patterns that occur during the process are way more interesting that the final results.


## Some more information
Transport equation for User-defined-scalars in Ansys Fluent can be found [Here](https://www.afs.enea.it/project/neptunius/docs/fluent/html/ug/node342.htm)

About parameters which generate interesting spatial patterns you can read [Here](https://www.mrob.com/pub/comp/xmorphia/pearson-classes.html)

There are more reaction diffusion systems however Gray-Scott is quite popular it is not easy to find parameters to create interesing patterns in other models. In order to change model you need to update source terms in the file gray_scott.c

## Spiral-Waves model
Mathematical model of nonlinear oscilator. Levels of u and v here describe deviations from the stationarity. Read more about in Mathematical Biology
II: Spatial Models and Biomedical Applications Third Edition by J.D. Murray or [Here](https://en.wikipedia.org/wiki/Belousov%E2%80%93Zhabotinsky_reaction). The model is of form:

$$
\begin{aligned}
\frac{\partial u}{\partial t} &= D_u \nabla^2 u +au - (u+bv)(u^2+v^2) \\
\frac{\partial v}{\partial t} &= D_v \nabla^2 v + av + (bu-v)(u^2+v^2)
\end{aligned}
$$

## Simulation Result
<img src="imgfiles/BW.png" alt="Pattern formation112" width="400"> **Parameters:** a = 3, b = -1, $D_u=2e-9$ $D_v=1e-8$ 
