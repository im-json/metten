#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

#include "input.h"

Eigen::MatrixXd metric(double space, Eigen::VectorXd vec);

Eigen::MatrixXd cartesian(double dim);

Eigen::Matrix2d polar(Eigen::Vector2d vec);

Eigen::Matrix3d cylindrical(Eigen::Vector3d vec);

Eigen::Matrix3d spherical(Eigen::Vector3d vec);

Eigen::MatrixXd hypercylindrical(Eigen::VectorXd vec);

Eigen::MatrixXd hyperspherical(Eigen::VectorXd vec);

double polyPath(struct Input in);
