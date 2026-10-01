#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <cctype>
#include <string>

#include "checks.h"

struct Input {
    double space;
    double dim;
    int riemCurveSign;
    std::vector<double> constants;
    std::vector<Eigen::VectorXd> points;
};

struct Input setup();

void getPoints(struct Input &in, int num);

Eigen::VectorXd point(double space, double dim);
