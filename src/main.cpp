#include <iostream>
#include <Eigen/Dense>

#include "value.h"
#include "input.h"
#include "metric.h"
#include "real.h"

int main() {
    struct Input in = setup();

    double exact, approx;

    if (in.space == "R") {
        exact = realDist(in);
        std::cout << "Exact distance: " << exact << std::endl;
    } else if (in.space == "S") {
        approx = polyPath(in);
        std::cout << "Approx distance: " << approx << std::endl;
    }

    return 0;
}
