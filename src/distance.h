#pragma once

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

#include "metric.h"

double distance(struct Input in);

Eigen::VectorXd CylinderToCart(Eigen::VectorXd vec);

Eigen::VectorXd BallToCart(Eigen::VectorXd vec);

double euclidean(struct Input in);

double posCurvature(struct Input in);

double negCurvature(struct Input in);
