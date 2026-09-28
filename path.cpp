#include "path.h"

double polypath(struct Input in) {
    int n;
    std::cout << "Set precision (how many steps):\n";
    std::cin >> n;

    Eigen::VectorXd prev, mid, delta;
    Eigen::VectorXd curr = in.p1;
    Eigen::VectorXd dist = in.p2 - in.p1;
    Eigen::VectorXd step = dist / n;

    double len = 0.0;

    for (int i = 0; i < n; i++) {
        prev = curr;
        curr += step;
        delta = curr - prev;
        mid = curr - (prev / 2);

        len += std::sqrt(delta.transpose() * metric(in.space, mid) * delta);
    }

    return len;
}