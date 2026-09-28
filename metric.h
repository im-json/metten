#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

#include "input.h"

Eigen::MatrixXd metric(int space, Eigen::VectorXd vec);

Eigen::MatrixXd cartesian(int dim);

Eigen::Matrix2d polar(Eigen::Vector2d vec);

Eigen::MatrixXd spherical(Eigen::VectorXd vec);
