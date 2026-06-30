# LEO Station-Keeping

Autonomous station-keeping of a satellite in low Earth orbit using closed-loop robust and LQ control. The project synthesizes a control law that holds a satellite on a circular reference orbit despite the main orbital perturbations, validates it in simulation with MATLAB/Simulink, and generates embedded C/C++ from the model using Embedded Coder.

## Overview

Traditional station-keeping is teleoperated from the ground: the satellite is tracked, a corrective impulse is computed on the ground when it drifts too far, and the maneuver is uplinked and verified. Onboard orbit determination now gives continuous, meter-level access to position and velocity, which makes a fully closed-loop, onboard strategy possible. That strategy lowers ground operations cost, improves positioning accuracy, and reduces propellant use, which extends satellite life.

This project builds the models, the controller, and the embedded code path for that closed-loop approach.

## Objective

Keep a satellite (the chaser) on a reference orbit (the target) despite perturbing forces. Two perturbations are modeled explicitly:

- J2, the first zonal harmonic of the Earth gravitational potential, which accounts for the oblateness of the Earth at the poles.
- Atmospheric drag, which dominates the non-gravitational perturbations at low altitude.

## Method

The work uses a two-model approach, consistent with model-based control design.

1. **Validation model (nonlinear).** A nonlinear state-space model of the absolute motion of a satellite in the geocentric inertial frame, including Keplerian gravity, the J2 term, and atmospheric drag. The state is the Cartesian position and velocity. This model is used to evaluate the controller in simulation.

2. **Synthesis model (linear).** The validation model is linearized around a circular reference orbit to obtain a model of the relative motion between a fictitious target satellite and the real chaser, expressed in a local frame. This yields the Clohessy-Wiltshire (Hill) equations, used to compute the control law.

The state vector of the linear model is the relative position and velocity in the local frame:

```
x = [ xi  eta  zeta  xi_dot  eta_dot  zeta_dot ]^T
```

and the model is written in the standard form `x_dot = A x + B u`, where `u` is the corrective thrust expressed in the local frame.

## Control design

State-feedback controllers are computed from the linear synthesis model by solving an LQ problem:

```matlab
K1 = lqr(A, B, eye(6), 1e12*eye(3));
K2 = lqr(A, B, eye(6), 1e14*eye(3));
```

The two weightings trade actuation effort against tracking aggressiveness, and both are simulated against the open-loop response.

## Embedded code generation

The control model is set up for automatic code generation with Embedded Coder, producing C/C++ source from the Simulink model. This follows a model-based design to code workflow: the controller is designed and validated in simulation, then the implementation is generated directly from the validated model rather than hand-coded.

The generated output includes the controller step function and its interface headers. By default the build folders are excluded from version control (see `.gitignore`), since they are reproducible from the model. A representative generated step function and header can be committed to document the workflow.

## Reference orbit

The reference orbit is that of the MICROSCOPE satellite (a circular, near-equatorial low Earth orbit).

| Parameter | Value | Unit |
|-----------|-------|------|
| Semi-major axis `a` | 7068 | km |
| Eccentricity `e` | 0 | - |
| Inclination `i` | 0 | rad |
| RAAN `Omega` | 0 | rad |
| Argument of perigee `omega` | 0 | rad |

Satellite characteristics used in the drag model: surface `S = 2 m^2`, drag coefficient `Cd = 2`, mass `m = 191.1 kg`, constant atmospheric density `rho0 = 6.3e-13 kg/m^3`.

## Repository structure

```
leo-station-keeping/
├── src/        MATLAB scripts, Simulink models, and generated C/C++
├── docs/       Project notes, methodology, and references
├── results/    Simulation figures and exported data
├── .gitignore
├── LICENSE
└── README.md
```

## Requirements

- MATLAB
- Simulink
- Control System Toolbox (for `lqr`)
- Embedded Coder / Simulink Coder (for C/C++ generation)

## How to run

1. Open MATLAB and add `src/` to the path.
2. Run the initialization script to set orbital and satellite parameters and convert the initial orbital elements to Cartesian state.
3. Open and run the Simulink validation model.
4. Run the simulation scripts to reproduce the open-loop and closed-loop responses.
5. To regenerate the embedded code, build the control model with Embedded Coder.

## What you can reproduce

- The target trajectory in the equatorial plane over one orbital period.
- The perturbed trajectory under J2 and drag over several orbital periods, showing the effect of each perturbation.
- Validation of the linearization by comparing the nonlinear and linear responses for the same relative initial conditions.
- The closed-loop response under the LQ controllers, with and without perturbations, against the open-loop baseline.
- The C/C++ implementation of the controller, generated from the validated model.

## Background

This project is based on a graduate control engineering study (Dynamique des Systemes Aeronautiques et Spatiaux) carried out at the University of Bordeaux / Bordeaux INP ENSEIRB-MATMECA. It applies robust and optimal control methods to a spacecraft application.

## Author

**Fils Elie Boungoueres**
Controls and Embedded Systems Engineer

GitHub: [@ElijahSon](https://github.com/ElijahSon)
LinkedIn: [fils-elie-boungoueres](https://linkedin.com/in/fils-elie-boungoueres)

Created and maintained by Fils Elie Boungoueres.

## License

Released under the MIT License. See [LICENSE](LICENSE). Copyright (c) Fils Elie Boungoueres.
