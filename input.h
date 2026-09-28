#pragma once

#include <iostream>
#include <Eigen/Dense>

#include "flags.h"

struct Input {
    int space;
    int dim;
    Eigen::VectorXd p1;
    Eigen::VectorXd p2;
};

struct Input setup();

Eigen::VectorXd point(int space, int dim);
