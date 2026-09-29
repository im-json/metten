#include <iostream>
#include <Eigen/Dense>

#include "flags.h"
#include "input.h"
#include "metric.h"
#include "distance.h"

int main() {
    struct Input in = setup();

    double exact = distance(in);

    std::cout << "Exact distance: " << exact << std::endl;

    return 0;
}
