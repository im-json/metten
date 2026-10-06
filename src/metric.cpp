#include "metric.h"

Eigen::MatrixXd metric(struct Input in, Eigen::VectorXd vec) {
    if (in.space == "R") {
        if (in.region == 1.0) {
            return cartesianReal(vec.size());
        } else if (in.region == 2.0) {
            return polarReal(vec);
        } else if (in.region == 3.0) {
            return solidCylinderReal(vec);
        } else if (in.region == 4.0) {
            return solidBallReal(vec);
        } else if (in.region == 6.0) {
            return solidHypercylinderReal(vec);
        } else if (in.region == 7.0) {
            return solidHyperballReal(vec);
        }
    } else if (in.space == "S") {
        if (in.region == 1.0) {
            return sphere(in.consts[0].val, vec);
        } else if (in.region == 2.0) {
            return hypersphere(in.consts[0].val, vec);
        }
    } else if (in.space == "T") {
        return Eigen::MatrixXd();
    }

    return Eigen::MatrixXd();
}

Eigen::MatrixXd cartesianReal(double d){
    if (d < 1) {
        std::cout << "Dimension must be a positive integer, dumbass\n";
        return Eigen::MatrixXd();
    }
    return Eigen::MatrixXd::Identity(d, d);
}

Eigen::Matrix2d polarReal(Eigen::Vector2d vec) {
    Eigen::Matrix2d g = Eigen::Matrix2d::Zero();

    if (vec.size() != 2) {
        std::cout << "Dimension != 2, dumbass.\n";
        return g;
    }

    double r = vec(0);

    g << 1, 0, 
         0, r*r;
    return g;
}

Eigen::Matrix3d solidCylinderReal(Eigen::Vector3d vec) {
    Eigen::Matrix3d g = Eigen::Matrix3d::Zero();

    if (vec.size() != 3) {
        std::cout << "Dimension != 3, dumbass\n";
        return g;
    }

    double r = vec(0);

    g << 1, 0, 0, 
         0, r*r, 0,
         0, 0, 1;
         
    return g;
}

Eigen::Matrix3d solidBallReal(Eigen::Vector3d vec) {
    Eigen::Matrix3d g = Eigen::Matrix3d::Zero();

    if (vec.size() != 3) {
        std::cout << "Dimension != 3, dumbass\n";
        return g;
    }

    g(0,0) = 1;
    g.diagonal().tail(2) = sphere(vec(0), vec.tail(2)).diagonal();

    return g;
}

Eigen::Matrix3d solidTorusReal(double a, Eigen::Vector3d vec) {
    Eigen::Matrix3d g = Eigen::Matrix3d::Zero();

    if (vec.size() != 3) {
        std::cout << "Dimension != 3, dumbass\n";
        return g;
    }

    g(0,0) = 1;
    g.diagonal().tail(2) = torus(a, vec(0), vec.tail(2)).diagonal();

    return g;
}

Eigen::MatrixXd solidHypercylinderReal(Eigen::VectorXd vec) {
    int d = vec.size();
    Eigen::MatrixXd g = Eigen::MatrixXd::Zero(d,d);

    if (d < 3) {
        std::cout << "Dimension must be >= 3, dumbass\n";
        return g;
    }

    double r = vec(0);

    g(1,1) = r*r;
    g.diagonal() = Eigen::VectorXd::Ones(d);

    return g;
}

Eigen::MatrixXd solidHyperballReal(Eigen::VectorXd vec) {
    int d = vec.size();
    Eigen::MatrixXd g = Eigen::MatrixXd::Zero(d,d);

    if (d < 3) {
        std::cout << "Dimension must be >= 3, dumbass\n";
        return g;
    }

    g(0,0) = 1;
    g.diagonal().tail(d - 1) = hypersphere(vec(0), vec.tail(d - 1)).diagonal();

    return g;
}

double polyPath(struct Input in) {
    int n;

    std::cout << "Set precision (how many steps):\n";
    std::cin >> n;

    Eigen::VectorXd prev, mid, delta;
    Eigen::VectorXd curr = in.points[0];
    Eigen::VectorXd dist = in.points[1] - in.points[0];
    Eigen::VectorXd step = dist / n;

    double len = 0.0;

    for (int i = 0; i < n; i++) {
        prev = curr;
        curr += step;
        delta = curr - prev;
        mid = curr - (prev / 2);

        len += std::sqrt(delta.transpose() * metric(in, mid) * delta);
    }

    return len;
}
