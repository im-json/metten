# metten

metten (named after **met**ric **ten**sor) is a geometric one-trick pony. Its singular purpose is to calculate the shortest distance between points on a Riemannian manifold. This tends to be easier said than done.

### Flat Manifolds
* Cartesian coordinates in $\mathbb{R}^n \quad (x_1,\dots,x_n)$
* Polar coordinates in $\mathbb{R}^2 \quad (r,\theta)$
* Cylindrical coordinates in $\mathbb{R}^3 \quad (r,\theta,z)$
* Spherical coordinates in $\mathbb{R}^3 \quad (r,\phi,\theta)$
* Hypercylindrical coordinates in $\mathbb{R}^n, \ n \ge 4 \quad (r,\phi_1,\dots,\theta,z)$
* Hyperspherical coordinates in $\mathbb{R}^n, \ n \ge 4 \quad (r,\phi_1,\dots,\theta)$

Flat manifolds are relatively simple cases. Euclidean space has zero Riemann curvature, and analytic solutions for shortest distance always exist.
Distance between two points is the $\ell^2$ norm of the difference between the Cartesian components of both points.

### Positive Curvature Manifolds
* Intrinsic spheres in $\mathbb{S}^n \quad (\phi,\theta)$ 

### Negative Curvature Manifolds
