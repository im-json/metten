#include "metric.h"

Eigen::MatrixXd metric(double space, Eigen::VectorXd vec) {
    if (space == 1.0) {
        return cartesian(vec.size());
    } else if (space == 2.0) {
        return polar(vec);
    } else if (space == 3.1) {
        return cylinderSolid(vec);
    } else if (space == 3.2) {
        return ballSolid(vec);
    } else if (space == 4.1) {
        return hypercylinderSolid(vec);
    } else if (space == 4.2) {
        return hyperballSolid(vec);
    }

    return Eigen::MatrixXd();
}

Eigen::MatrixXd cartesian(double dim){
    if (dim < 1) {
        std::cout << "Dimension must be >= 3, dumbass" << std::endl;
        return Eigen::MatrixXd();
    }
    return Eigen::MatrixXd::Identity(dim, dim);
}

Eigen::Matrix2d polar(Eigen::Vector2d vec) {
    if (vec.size() != 2) {
        std::cout << "Dimension != 2, dumbass" << std::endl;
        return Eigen::Matrix2d();
    }

    double r = vec(0);

    Eigen::Matrix2d mat;
    mat << 1, 0, 
           0, r*r;
    return mat;
}

Eigen::Matrix3d cylinderSolid(Eigen::Vector3d vec) {
    if (vec.size() != 3) {
        std::cout << "Dimension != 3, dumbass" << std::endl;
        return Eigen::Matrix3d();
    }

    double r = vec(0);

    Eigen::Matrix3d mat;
    mat << 1, 0, 0, 
           0, r*r, 0,
           0, 0, 1;
    return mat;
}

Eigen::Matrix3d ballSolid(Eigen::Vector3d vec) {
    if (vec.size() != 3) {
        std::cout << "Dimension != 3, dumbass" << std::endl;
        return Eigen::Matrix3d();
    }

    double r = vec(0);
    double phi = vec(1);

    Eigen::Matrix3d mat;
    mat << 1, 0, 0, 
           0, r*r, 0,
           0, 0, r*r*std::sin(phi)*std::sin(phi);
    return mat;
}

Eigen::MatrixXd hypercylinderSolid(Eigen::VectorXd vec) {
    int d = vec.size();

    if (d < 4) {
        std::cout << "Dimension must be >= 4, dumbass" << std::endl;
        return Eigen::MatrixXd();
    }

    Eigen::MatrixXd mat = Eigen::MatrixXd::Zero(d, d);
    Eigen::VectorXd diag = Eigen::VectorXd::Ones(d);

    double r = vec(0);

    diag(1) = r*r;

    mat.diagonal() += diag;

    return mat;
}

Eigen::MatrixXd hyperballSolid(Eigen::VectorXd vec) {
    int d = vec.size();

    if (d < 4) {
        std::cout << "Dimension must be >= 4, dumbass" << std::endl;
        return Eigen::MatrixXd();
    }

    Eigen::MatrixXd mat = Eigen::MatrixXd::Zero(d, d);
    Eigen::VectorXd diag(d);

    double r = vec(0);
    double elem = r*r;

    diag(0) = 1;
    diag(1) = r*r;
    
    for (int i = 1; i < d - 1; i++) {
        elem *= std::sin(vec(i)) * std::sin(vec(i));
        diag(i + 1) = elem;
    }

    mat.diagonal() += diag;

    return mat;
}

double polyPath(struct Input in) {
    int n;
    std::cout << "Set precision (how many steps):\n";
    std::cin >> n;

    Eigen::VectorXd prev, mid, delta;
    Eigen::VectorXd curr = in.p1;
    Eigen::VectorXd dist = in.p2 - in.p1;
    Eigen::VectorXd step = dist / n;

    double len = 0.0;

    for (int i = 0; i < n; i++) {
        prev = curr;
        curr += step;
        delta = curr - prev;
        mid = curr - (prev / 2);

        len += std::sqrt(delta.transpose() * metric(in.space, mid) * delta);
    }

    return len;
}
