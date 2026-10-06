#include "torus.h"

Eigen::Matrix2d torus(double a, double r, Eigen::Vector2d vec) {
    Eigen::Matrix2d g = Eigen::Matrix2d::Zero();

    if (vec.size() != 2) {
        std::cout << "Dimension != 2, dumbass\n";
        return g;
    }

    double phi = vec(0);
    double R = r + a;

    g(0,0) = r*r;
    g(1,1) = (R + r*std::cos(phi))*(R + r*std::cos(phi));

    return g;
}