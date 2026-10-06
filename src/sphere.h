#pragma once

#include <iostream>
#include <Eigen/Dense>

Eigen::Matrix2d sphere(double r, Eigen::Vector2d vec);

Eigen::MatrixXd hypersphere(double r, Eigen::VectorXd vec);
