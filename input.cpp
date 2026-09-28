#include "input.h"

struct Input setup() {
    struct Input in;

    std::cout << "Select a coordinate system:\n";
    std::cout << "Type 1 for Cartesian\nType 2 for Polar\nType 3 for Spherical\n";
    std::cin >> in.space;

    while (in.space < 1 || in.space > 3) {
        std::cout << "Enter a valid capital letter, dumbass. ";
        std::cout << "Select a coordinate system:\n";
        std::cout << "Type 1 for Cartesian\nType 2 for Polar\nType 3 for Spherical\n";
        std::cin >> in.space;
    }

    if (in.space != 2) {
        std::cout << "Enter dimension:\n";
        std::cin >> in.dim;
    } else if (in.space == 2) {
        in.dim = 2;
    }

    if (in.space == 1) {
        std::cout << "Enter point 1 in the form x1,...,xn:\n";
        in.p1 = point(in.space, in.dim);
        std::cout << "Enter point 2 in the form x1,...,xn:\n";
        in.p2 = point(in.space, in.dim);
    } else if (in.space == 2) {
        std::cout << "Enter point 1 in the form r,phi. ";
        std::cout << "Use radians for phi (e.g. 2*PI):\n";
        in.p1 = point(in.space, 2);
        std::cout << "Enter point 2 in the form r,phi. ";
        std::cout << "Use radians for phi (e.g. 2*PI):\n";
        in.p2 = point(in.space, 2);
    } else if (in.space == 3) {
        std::cout << "Enter point 1 in the form r,theta1,...,phi. ";
        std::cout << "Use radians for thetas and phi (e.g. 2.5PI):\n";
        in.p1 = point(in.space, in.dim);
        std::cout << "Enter point 2 in the form r,theta1,...,phi:\n";
        std::cout << "Use radians for thetas and phi (e.g. 2.5PI):\n";
        in.p2 = point(in.space, in.dim);
    }

    return in;
}

Eigen::VectorXd point(int space, int dim) {
    std::vector<double> vec;
    while (!isValid(space, dim, vec)) {
        vec.clear();
    }

    // Eigen::VectorXd v = Eigen::Map<Eigen::VectorXd>(vec.data(), vec.size());
    // std::cout << v << '\n';
    
    return Eigen::Map<Eigen::VectorXd>(vec.data(), vec.size());
}
