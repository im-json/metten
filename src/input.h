#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <cctype>
#include <string>

#include "value.h"

enum class Coords {
    Cartesian = 1,
    Spherical = 2
};

struct Input {
    double space;
    double dim;
    int riemCurveSign;
    Coords coords;
    std::vector<Value> params;
    std::vector<Value> consts;
    std::vector<Eigen::VectorXd> points;
};

struct Input setup();

void setupSpace(struct Input &in);

void setupDim(struct Input &in);

void setupCoords(struct Input &in);

void setupConsts(struct Input &in);

void setupParams(struct Input &in);

void setupPoints(struct Input &in);
