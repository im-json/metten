#include <iostream>
#include <Eigen/Dense>

#include "flags.h"
#include "input.h"
#include "metric.h"
#include "path.h"

int main() {
    struct Input in = setup();

    double len = polypath(in);

    std::cout << "Length is: " << len << std::endl;

    return 0;
}
