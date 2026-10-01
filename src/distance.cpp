#include "distance.h"

double distance(struct Input in) {
    if (!in.riemCurveSign) {
        return (cartComponent(in, 1) - cartComponent(in, 0)).norm();
    } else if (in.riemCurveSign == 1) {
        return posCurvature(in);
    } else if (in.riemCurveSign == -1) {
        return negCurvature(in);
    }

    return -1;
}

Eigen::VectorXd polarToCart(Eigen::VectorXd vec) {
    Eigen::VectorXd cartComponent{{ vec(0)*std::cos(vec(1)), vec(0)*std::sin(vec(1)) }};

    return cartComponent;
}

Eigen::VectorXd cylinderToCart(Eigen::VectorXd vec) {
    double z = vec(vec.size() - 1);

    vec.conservativeResize(vec.size() - 1);
    vec = ballToCart(vec);
    vec.conservativeResize(vec.size() + 1);
    vec(vec.size() - 1) = z;

    return vec;
}

Eigen::VectorXd ballToCart(Eigen::VectorXd vec) {
    Eigen::VectorXd cartComponent = vec;

    double r = vec(0);
    double prodSin = 1;

    for (int i = 0; i < vec.size() - 1; i++) {
        cartComponent(i) = r*prodSin*std::cos(cartComponent(i + 1));
        prodSin *= std::sin(vec(i + 1));
    }

    cartComponent(vec.size() - 1) = r*prodSin;

    // std::cout << cartComponent << std::endl;
        
    return cartComponent;
}

Eigen::VectorXd cartComponent(struct Input in, int num) {
    if (in.space == 1.0) {
        return in.points[num];
    } else if (in.space == 2.0) {
        return polarToCart(in.points[num]);
    } else if (in.space == 3.1 || in.space == 4.1) {
        return cylinderToCart(in.points[num]);
    } else if (in.space == 3.2 || in.space == 4.2) {
        return ballToCart(in.points[num]);
    }

    return Eigen::VectorXd();
}

double posCurvature(struct Input in) {
    return -1;
}

double negCurvature(struct Input in) {
    return -1;
}
