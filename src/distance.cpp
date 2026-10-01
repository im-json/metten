#include "distance.h"

double distance(struct Input in) {
    if (!in.riemCurveSign) {
        return euclidean(in);
    } else if (in.riemCurveSign == 1) {
        return posCurvature(in);
    } else if (in.riemCurveSign == -1) {
        return negCurvature(in);
    }

    return -1;
}

Eigen::VectorXd CylinderToCart(Eigen::VectorXd vec) {
    Eigen::VectorXd cartComponent = vec;
    double r = vec(0);
    double prodSin = 1;
    for (int i = 0; i < vec.size() - 2; i++) {
        cartComponent(i) = r*prodSin*std::cos(cartComponent(i + 1));
        prodSin *= std::sin(vec(i + 1));
    }
    cartComponent(vec.size() - 2) = r*prodSin;

    return cartComponent;
}

Eigen::VectorXd BallToCart(Eigen::VectorXd vec) {
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

double euclidean(struct Input in) {
    if (in.space == 1.0) {
        return (in.points[1] - in.points[0]).norm();
    } else if (in.space == 2.0) {
        double r1 = in.points[0](0), r2 = in.points[1](0);
        double phi1 = in.points[0](1), phi2 = in.points[1](1);
        return std::sqrt(r1*r1 + r2*r2 - 2*r1*r2*std::cos(phi2 - phi1));
    } else if (in.space == 3.1 || in.space == 4.1) {
        Eigen::VectorXd p1CartComponent = CylinderToCart(in.points[0]);
        Eigen::VectorXd p2CartComponent = CylinderToCart(in.points[1]);
        return (p2CartComponent - p1CartComponent).norm();
    } else if (in.space == 3.2 || in.space == 4.2) {
        Eigen::VectorXd p1CartComponent = BallToCart(in.points[0]);
        Eigen::VectorXd p2CartComponent = BallToCart(in.points[1]);
        return (p2CartComponent - p1CartComponent).norm();
    }

    return -1;
}

double posCurvature(struct Input in) {
    return -1;
}

double negCurvature(struct Input in) {
    return -1;
}
