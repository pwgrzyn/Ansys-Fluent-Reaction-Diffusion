# Ansys-Fluent-Reaction-Diffusion
Simulations of reaction diffusion models. Autocatalytic reaction given by Gray-Scott model showing the phenomenon of Turing Instability and autocatalytic Belousev-Zhabotinsky reaction. Simulations are made on a domain being a square(58mm) with periodic boundary conditions meaning that the substance freely flows through the boundary and appears on the other side. 

## How To Set this up in Ansys Student 2025
1. Create new Ansys Fluent project
2. Straight up open Setup
3. Import file Setup.cas.h5(or Setup_BZ.cas.h5 for Belousev-Zhabotinsky reaction) using Case import in Fluent. Setup.cas.h5 file contains information about mesh and all solver settings that are needed to solve the Reaction-Diffusion system for 2 scalars.
4. Head to User-Defined tab and add gray_scott.c(Oreg.c for BZ reaction) file as compiled build using libudf and load. Check if udf_init is present in function hooks tab.
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


## The Belousev-Zhabotinsky reaction
The Belousev-Zhaboitnsky reaction can be described with following chemical equations:

$$
\begin{aligned}
\text{BrO}_3^- + \text{Br}^- + 2\text{H}^+ &\xrightarrow{k_1} \text{HBrO}_2 + \text{HOBr} \\
\text{HBrO}_2 + \text{Br}^- + \text{H}^+ &\xrightarrow{k_2} 2\text{HOBr} \\
\text{BrO}_3^- + \text{HBrO}_2 + \text{H}^+ + 2\text{M}^{2+} &\xrightarrow{k_3} 2\text{HBrO}_2 + 2\text{M}^{3+} + \text{H}_2\text{O} \\
2\text{HBrO}_2 &\xrightarrow{k_4} \text{BrO}_3^- + \text{HOBr} + \text{H}^+ \\
2\text{M}^{3+} + \text{MA} + \text{BrMA} &\xrightarrow{k_5} f\text{Br}^- + 2\text{M}^{2+} + \text{Other products.}
\end{aligned}
$$

The mechanism involves three main processes: Autocatalysis of bromide acid equation 3, inhibition by bromide ion equation 1 and 2, resetting the cycle equation 4 and 5.

With substitution 

$$ 
A=BrO_3^-, W=Br^-, H=H^+, U=HBrO_2, P=HOBr, V=\text{ oxidized form of catalyst} , B=MA+BrMA
$$

we obtain the general form of the system

$$
\begin{aligned}
\mathbf{A} + \mathbf{W} + 2\mathbf{H} &\xrightarrow{k_1} \mathbf{U} + \mathbf{P} \\
\mathbf{U} + \mathbf{W} + \mathbf{H} &\xrightarrow{k_2} 2\mathbf{P} \\
\mathbf{A} + \mathbf{U} + \mathbf{H} &\xrightarrow{k_3} 2\mathbf{U} + 2\mathbf{V} \\
2\mathbf{U} &\xrightarrow{k_4} \mathbf{A} + \mathbf{P} + \mathbf{H} \\
\mathbf{V} + \mathbf{B} &\xrightarrow{k_5} \frac{1}{2}f\mathbf{W}
\end{aligned}
$$

where MA denotes malonic acid. A and B are major reactants hence their concentrations are considered constant respectively noted as a and b. Reaction is carried out in acidic enviroment so we have excess of hydrogen ions and any time and we consider H constant aswell. P is product of the reaction that is accumulated but nowhere used therefore it is not of our interest to track the P in simulations.

Since we are mostly interested in change of U,V and W from chemical equations we obtain following system of differential equations 

$$
\begin{aligned}
\frac{dU}{dT} &= k_1 a W H^2 - k_2 U W H + k_3 b U H - 2k_4 U^2 \\
\frac{dV}{dT} &= 2k_3 a U H - k_5 b V \\
\frac{dW}{dT} &= -k_1 a W H^2 - k_2 U W H + \frac{1}{2} k_5 f b V
\end{aligned}
$$

By substitution 

$$
t=k_5bT, u=\frac{k_3aU}{K_5b}, v=\frac{k_1k_3a^2V}{k_2k_5b}, w=\frac{k_2W}{k_3a}, \varepsilon=\frac{k_5b}{h_0k_3a}, \varepsilon'=\frac{2k_4k_5b}{h_0^2k_2k_3b}, q=\frac{2k_1k_4}{k_2k_3}, h=\frac{2k_1k_3a^2}{k_2k_5}H=\frac{1}{h_0}H
$$

and addintion of the diffusion therm we obtain dimensionless system given by 

$$
\begin{aligned}
\varepsilon \frac{du}{dt} &= \frac{1}{2} w h^2 - u w h + u h - q u^2 +D_u\nabla^2u\\
\frac{dv}{dt} &= u h - v +D_v\nabla^2v \\
\varepsilon' \frac{dw}{dt} &= -q w h^2 - 2q u w h + 2q f v+D_w\nabla^2w
\end{aligned}
$$

## Simulations

![HBrO](imgfiles/u-animation.gif)
