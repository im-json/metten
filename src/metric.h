#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

#include "input.h"
#include "sphere.h"
#include "torus.h"

Eigen::MatrixXd metric(struct Input in, Eigen::VectorXd vec);

Eigen::MatrixXd cartesianReal(double dim);

Eigen::Matrix2d polarReal(Eigen::Vector2d vec);

Eigen::Matrix3d solidCylinderReal(Eigen::Vector3d vec);

Eigen::Matrix3d solidBallReal(Eigen::Vector3d vec);

Eigen::Matrix3d solidTorusReal(double a, Eigen::Vector3d vec);

Eigen::MatrixXd solidHypercylinderReal(Eigen::VectorXd vec);

Eigen::MatrixXd solidHyperballReal(Eigen::VectorXd vec);

double polyPath(struct Input in);
