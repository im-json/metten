#include "input.h"

struct Input setup() {
    struct Input in;

    in.space = 0.0;
    in.dim = 0.0;

    while (in.space < 1.0 || in.space > 4.2) {
        std::cout << "Select a region:\n";
        std::cout << "Type 1 for Cartesian in R^n\n";
        std::cout << "Type 2 for Polar in R^2\n";
        // std::cout << "Type 2.2 for 2-cylinder (hollow)\n";
        // std::cout << "Type 2.3 for 2-sphere S^2 (hollow)\n";
        // std::cout << "Type 2.4 for 2-torus T^2 (hollow)\n";
        // std::cout << "Type 2.5 for 2-cone (hollow)\n";
        std::cout << "Type 3.1 for Cylinder in R^3 (solid)\n";
        std::cout << "Type 3.2 for Ball in R^3 (solid)\n";
        // std::cout << "Type 3.3 for Torus in R^3 (solid)\n";
        // std::cout << "Type 3.4 for Cone in R^3 (solid)\n";
        // std::cout << "Type 3.5 for n-sphere S^n (hollow)\n";
        // std::cout << "Type 2.4 for n-torus T^n (hollow)\n";
        std::cout << "Type 4.1 for Hypercylinder in R^n (solid)\n";
        std::cout << "Type 4.2 for Hyperball in R^n (solid)\n";
        std::cin >> in.space;

        if (in.space < 1.0 || in.space > 4.2) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid number, dumbass.\n";
        }
    }

    double minDim = std::floor(in.space);

    if (in.space == 4.1 || in.space == 4.2) {
        while (in.dim < minDim || std::floor(in.dim) != in.dim) {
            std::cout << "Enter dimension:\n";
            std::cin >> in.dim;

            if (in.dim < minDim || std::floor(in.dim) != in.dim) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter an integer >= " << minDim << ", dumbass.\n";
            }
        }
    } else {
        in.dim = std::floor(minDim);
    }

    getPoints(in, 0);
    getPoints(in, 1);

    return in;
}

void getPoints(struct Input &in, int num) {
    in.riemCurveSign = 0;

    if (in.space == 1.0) {
        std::cout << "Enter point " << num + 1 << " in the form x1,...,xn:\n";
    } else if (in.space == 2.0) {
        std::cout << "Enter point " << num + 1 << " 1 in the form r,theta. ";
        std::cout << "Use radians for theta (e.g. 2*PI):\n";
    } else if (in.space == 3.1) {
        std::cout << "Enter point " << num + 1 << " in the form r,theta,z. ";
        std::cout << "Use radians for theta (e.g. 2*PI):\n";
    } else if (in.space == 3.2) {
        std::cout << "Enter point " << num + 1 << " in the form r,phi,theta. ";
        std::cout << "Use radians for phi and theta (e.g. 2*PI):\n";
    } else if (in.space == 4.1) {
        std::cout << "Enter point " << num + 1 << " in the form r,phi1,...,theta,z. ";
        std::cout << "Use radians for phis and theta (e.g. 2*PI):\n";
    } else if (in.space == 4.2) {
        std::cout << "Enter point " << num + 1 << " in the form r,phi1,...,theta. ";
        std::cout << "Use radians for phis and theta (e.g. 2*PI):\n";
    }

    in.points.push_back(point(in.space, std::floor(in.dim)));
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
