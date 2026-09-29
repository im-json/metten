#include "input.h"

struct Input setup() {
    struct Input in;

    in.space = 0.0;
    in.dim = 0.0;

    while (in.space < 1.0 || in.space > 4.2) {
        std::cout << "Select a region:\n";
        std::cout << "Type 1 for Cartesian (solid, in R^n)\n";
        std::cout << "Type 2 for Polar (solid, in R^2)\n";
        std::cout << "Type 3.1 for Cylinder (solid, in R^3)\n";
        std::cout << "Type 3.2 for Sphere (solid, in R^3)\n";
        std::cout << "Type 4.1 for Hypercylinder (solid, in R^n)\n";
        std::cout << "Type 4.2 for Hypersphere (solid, in R^n)\n";
        std::cin >> in.space;

        if (in.space < 1.0 || in.space > 4.2) {
            std::cout << "Enter a valid number, dumbass.\n";
        }
    }

    double minDim = std::floor(in.space);

    if (in.space == 4.1 || in.space == 4.2) {
        while (in.dim < minDim || !isInteger(in.dim)) {
            std::cout << "Enter dimension:\n";
            std::cin >> in.dim;

            if (in.dim < minDim || !isInteger(in.dim)) {
                std::cout << "Enter an integer >= " << minDim << ", dumbass.\n";
            }
        }
    } else {
        in.dim = std::floor(minDim);
    }

    getPoints(in);

    return in;
}

void getPoints(struct Input &in) {
    if (in.space == 1.0) {
        in.riemCurveSign = 0;
        std::cout << "Enter point 1 in the form x1,...,xn:\n";
        in.p1 = point(in.space, in.dim);
        std::cout << "Enter point 2 in the form x1,...,xn:\n";
        in.p2 = point(in.space, in.dim);
    } else if (in.space == 2.0) {
        in.riemCurveSign = 0;
        std::cout << "Enter point 1 in the form r,theta. ";
        std::cout << "Use radians for theta (e.g. 2*PI):\n";
        in.p1 = point(in.space, 2);
        std::cout << "Enter point 2 in the form r,theta. ";
        std::cout << "Use radians for theta (e.g. 2*PI):\n";
        in.p2 = point(in.space, 2);
    } else if (in.space == 3.1) {
        in.riemCurveSign = 0;
        std::cout << "Enter point 1 in the form r,theta,z. ";
        std::cout << "Use radians for theta (e.g. 2*PI):\n";
        in.p1 = point(in.space, 3);
        std::cout << "Enter point 2 in the form r,theta,z. ";
        std::cout << "Use radians for theta (e.g. 2*PI):\n";
        in.p2 = point(in.space, 3);
    } else if (in.space == 3.2) {
        in.riemCurveSign = 0;
        std::cout << "Enter point 1 in the form r,phi,theta. ";
        std::cout << "Use radians for phi and theta (e.g. 2*PI):\n";
        in.p1 = point(in.space, 3);
        std::cout << "Enter point 2 in the form r,phi,theta. ";
        std::cout << "Use radians for phi and theta (e.g. 2*PI):\n";
        in.p2 = point(in.space, 3);
    } else if (in.space == 4.1) {
        in.riemCurveSign = 0;
        std::cout << "Enter point 1 in the form r,phi1,...,theta,z. ";
        std::cout << "Use radians for phis and theta (e.g. 2PI):\n";
        in.p1 = point(in.space, in.dim);
        std::cout << "Enter point 2 in the form r,phi1,...,theta,z. ";
        std::cout << "Use radians for phis and theta (e.g. 2PI):\n";
        in.p2 = point(in.space, in.dim);
    } else if (in.space == 4.2) {
        in.riemCurveSign = 0;
        std::cout << "Enter point 1 in the form r,phi1,...,theta. ";
        std::cout << "Use radians for phis and theta (e.g. 2PI):\n";
        in.p1 = point(in.space, in.dim);
        std::cout << "Enter point 2 in the form r,phi1,...,theta. ";
        std::cout << "Use radians for phis and theta (e.g. 2PI):\n";
        in.p2 = point(in.space, in.dim);
    }
}

Eigen::VectorXd point(double space, double dim) {
    std::vector<double> vec;
    while (!validVector(space, dim, vec)) {
        vec.clear();
    }

    // Eigen::VectorXd v = Eigen::Map<Eigen::VectorXd>(vec.data(), vec.size());
    // std::cout << v << '\n';
    
    return Eigen::Map<Eigen::VectorXd>(vec.data(), vec.size());
}
