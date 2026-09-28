#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>

bool isValid(int space, int dim, std::vector<double> &vec);

bool isExpression(std::string &elem);

bool isDouble(std::string elem);

bool hasSubstring(std::string &str, std::string substr);

void eraseSubstring(std::string &str, std::string substr);

bool inRadians(std::string elem);

bool inDomain(int space, int dim, std::vector<double> vec);