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

bool validVector(double space, double dim, std::vector<double> &vec);

bool validElement(std::string &elem, std::vector<double> &vec);

bool isDouble(std::string elem);

bool hasSubstring(std::string &str, std::string substr);

void eraseSubstring(std::string &str, std::string substr);

bool inRadians(std::string elem);

bool inDomain(double space, double dim, std::vector<double> vec);

bool isInteger(double a);

bool validRadius(double r);

bool validZenith(double phi, int i);

bool validAzimuth(double theta);
