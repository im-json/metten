# metten

metten is a geometric one-trick pony, written in C++14.
Its singular purpose is to calculate the shortest distance between points on a Riemannian manifold.
This is often easier said than done.
Analytic solutions are found where possible, otherwise gradient descent is used for approximation.

### Flat Manifolds
* Cartesian in $\mathbb{R}^n \quad (x_1,\dots,x_n)$
* Polar in $\mathbb{R}^2 \quad (r,\theta)$
* Cylinder in $\mathbb{R}^3$ (solid) $\quad (r,\theta,z)$
* Ball in $\mathbb{R}^3$ (solid) $\quad (r,\phi,\theta)$
* Torus in $\mathbb{R}^3$ (solid) $\quad (s,\phi,\theta)$
* Hypercylinder in $\mathbb{R}^n$ (solid) $\quad (r,\phi_1,\dots,\theta,z)$
* Hyperball in $\mathbb{R}^n$ (solid) $\quad (r,\phi_1,\dots,\theta)$
* Torus in $\mathbb{R}^n$ (solid) $\quad (r,\phi_1,\dots,\theta)$

Flat manifolds are relatively simple cases.
Euclidean space has zero Riemann curvature, and analytic solutions for shortest distance always exist.
Distance between two points is the $\ell^2$ norm of the difference between the Cartesian components of both points.

### Positive Curvature Manifolds
* 2-sphere $\mathbb{S}^2$ (hollow) $\quad (\phi,\theta)$
* n-sphere $\mathbb{S}^n$ (hollow) $\quad (\phi_1,\dots,\theta)$

### Negative Curvature Manifolds

### Mixed Curvature Manifolds
* 2-torus $\mathbb{T}^2$ (hollow) $\quad (\theta_1,\theta_2)$
* n-torus $\mathbb{T}^n$ (hollow) $\quad (\theta_1,\dots,\theta_n)$