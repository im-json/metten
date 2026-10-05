#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

#include "metric.h"

double realDist(struct Input in);

Eigen::VectorXd polarToCart(Eigen::VectorXd vec);

Eigen::VectorXd cylinderToCart(Eigen::VectorXd vec);

Eigen::VectorXd ballToCart(Eigen::VectorXd vec);

Eigen::VectorXd cartComponent(struct Input in, int num);

double posCurvature(struct Input in);

double negCurvature(struct Input in);
