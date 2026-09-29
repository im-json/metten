#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

#include "input.h"

Eigen::MatrixXd metric(double space, Eigen::VectorXd vec);

Eigen::MatrixXd cartesian(double dim);

Eigen::Matrix2d polar(Eigen::Vector2d vec);

Eigen::Matrix3d cylinder(Eigen::Vector3d vec);

Eigen::Matrix3d sphere(Eigen::Vector3d vec);

Eigen::MatrixXd hypercylinder(Eigen::VectorXd vec);

Eigen::MatrixXd hypersphere(Eigen::VectorXd vec);

double polyPath(struct Input in);
