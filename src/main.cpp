#include <iostream>
#include <Eigen/Dense>

#include "value.h"
#include "input.h"
#include "metric.h"
#include "real.h"

int main() {
    struct Input in = setup();

    double exact = realDist(in);

    std::cout << "Exact distance: " << exact << std::endl;

    return 0;
}
