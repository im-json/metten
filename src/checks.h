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

bool validVector(double space, double dim, std::vector<double> &vec);

bool inDomain(double space, double dim, std::vector<double> vec);

bool isInteger(double a);

bool validRadius(double r);

bool validZenith(double phi, int i);

bool validAzimuth(double theta);
