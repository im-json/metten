#pragma once

#include <iostream>
#include <Eigen/Dense>

#include "flags.h"

struct Input {
    double space;
    double dim;
    int riemCurveSign;
    Eigen::VectorXd p1;
    Eigen::VectorXd p2;
};

struct Input setup();

void getPoints(struct Input &in);

Eigen::VectorXd point(double space, double dim);
