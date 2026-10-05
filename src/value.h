#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <cmath>

#include "../parser/calculator.h"

struct Value {
    double val;
    std::string name;
    std::array<bool, 2> closed;
    std::array<double, 2> bounds;
};

void readConsts(std::vector<Value> &consts);

void readParams(std::vector<Value> &params);

Eigen::VectorXd readPoint(std::vector<Value> &params);

bool validValues(std::vector<Value> &vec);

void printPi(double val);

bool inDomain(struct Value &val);

void real(struct Value &v, std::string name);

void positive(struct Value &v, std::string name);

void nonNeg(struct Value &v, std::string name);

void zenith(struct Value &v, std::string name);

void azimuth(struct Value &v, std::string name);
