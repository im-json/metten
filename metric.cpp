#include "metric.h"

Eigen::MatrixXd metric(int space, Eigen::VectorXd vec) {
    if (space == 1) {
        return cartesian(vec.size());
    } else if (space == 2) {
        return polar(vec);
    } else if (space == 3) {
        return spherical(vec);
    }

    return Eigen::MatrixXd();
}

Eigen::MatrixXd cartesian(int d){
    if (d < 1) {
        std::cout << "Dimension must be >= 3, dumbass" << std::endl;
        return Eigen::MatrixXd();
    }
    return Eigen::MatrixXd::Identity(d, d);
}

Eigen::Matrix2d polar(Eigen::Vector2d vec) {
    if (vec.size() != 2) {
        std::cout << "Dimension != 2, dumbass" << std::endl;
        return Eigen::MatrixXd();
    }

    double r = vec(0);

    Eigen::Matrix2d mat;
    mat << 1, 0, 
           0, r*r;
    return mat;
}

Eigen::MatrixXd spherical(Eigen::VectorXd vec) {
    int d = vec.size();

    if (d < 3) {
        std::cout << "Dimension must be >= 3, dumbass" << std::endl;
        return Eigen::MatrixXd();
    }

    Eigen::MatrixXd mat = Eigen::MatrixXd::Zero(d, d);
    Eigen::VectorXd diag(d);

    double r = vec(0);
    double elem = r*r;

    diag(0) = 1;
    diag(1) = elem;
    
    for (int i = 2; i < d; i++) {
        elem *= std::sin(vec(i)) * std::sin(vec(i));
        diag(i) = elem;
    }

    mat.diagonal() += diag;

    return mat;
}
