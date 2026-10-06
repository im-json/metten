#include "sphere.h"

Eigen::Matrix2d sphere(double r, Eigen::Vector2d vec) {
    Eigen::Matrix2d g = Eigen::Matrix2d::Zero();

    if (vec.size() != 2) {
        std::cout << "Dimension != 2, dumbass\n";
        return g;
    }

    double phi = vec(0);

    g(0,0) = r*r;
    g(1,1) = r*r*std::sin(phi)*std::sin(phi);

    return g;
}

Eigen::MatrixXd hypersphere(double r, Eigen::VectorXd vec) {
    int d = vec.size();
    Eigen::MatrixXd g = Eigen::MatrixXd::Zero(d,d);

    if (d < 1) {
        std::cout << "Dimension must be a positive integer, dumbass\n";
        return g;
    }

    double elem = r*r;

    g(0,0) = elem;

    for (int i = 0; i < d - 1; i++) {
        elem *= std::sin(vec(i)) * std::sin(vec(i));
        g(i + 1, i + 1) = elem;
    }

    return g;
}
