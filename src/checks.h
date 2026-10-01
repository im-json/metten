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

bool validVector(double space, double dim, std::vector<double> constants, std::vector<double> &vec);

bool inDomain(double space, double dim, std::vector<double> constants, std::vector<double> vec);

bool isInteger(double a);

bool validRadius(double r);

bool validMajorRadius(double r, double a);

bool validZenith(double x, std::string name);

bool validAzimuth(double x, std::string name);
