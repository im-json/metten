#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

#include "input.h"

Eigen::MatrixXd metric(struct Input in, Eigen::VectorXd vec);

Eigen::MatrixXd cartesian(double dim);

Eigen::Matrix2d polar(Eigen::Vector2d vec);

Eigen::Matrix3d cylinderSolid(Eigen::Vector3d vec);

Eigen::Matrix3d ballSolid(Eigen::Vector3d vec);

Eigen::Matrix3d torusSolid(struct Input in, Eigen::Vector3d vec);

Eigen::MatrixXd hypercylinderSolid(Eigen::VectorXd vec);

Eigen::MatrixXd hyperballSolid(Eigen::VectorXd vec);

double polyPath(struct Input in);
