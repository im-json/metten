#include "input.h"

struct Input setup() {
    struct Input in;

    in.space = 0.0;
    in.dim = 0.0;
    in.consts.resize(0);

    setupSpace(in);
    setupDim(in);
    setupConsts(in);
    setupParams(in);
    setupPoints(in);

    return in;
}

void setupSpace(struct Input &in) {
    while (in.space < 1.0 || in.space > 4.2) {
        std::cout << "Select a region:\n";
        std::cout << "Type 1 for Cartesian in R^n\n";
        std::cout << "Type 2 for Polar in R^2\n";
        // std::cout << "Type 2.2 for 2-cylinder (hollow)\n";
        // std::cout << "Type 2.3 for 2-sphere S^2 (hollow)\n";
        // std::cout << "Type 2.4 for 2-torus T^2 (hollow)\n";
        // std::cout << "Type 2.5 for 2-cone (hollow)\n";
        std::cout << "Type 3.1 for Cylinder in R^3 (solid)\n";
        std::cout << "Type 3.2 for Ball in R^3 (solid)\n";
        std::cout << "Type 3.3 for Torus in R^3 (solid)\n";
        // std::cout << "Type 3.4 for Cone in R^3 (solid)\n";
        // std::cout << "Type 3.5 for n-sphere S^n (hollow)\n";
        // std::cout << "Type 2.4 for n-torus T^n (hollow)\n";
        std::cout << "Type 4.1 for Hypercylinder in R^n (solid)\n";
        std::cout << "Type 4.2 for Hyperball in R^n (solid)\n";
        std::cin >> in.space;

        if (in.space < 1.0 || in.space > 4.2) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid number, dumbass.\n";
        }
    }
}

void setupDim(struct Input &in) {
    int minDim = static_cast<int>(std::floor(in.space));

    if (in.space == 4.1 || in.space == 4.2) {
        while (in.dim < minDim || std::floor(in.dim) != in.dim) {
            std::cout << "Enter dimension:\n";
            std::cin >> in.dim;

            if (in.dim < minDim || std::floor(in.dim) != in.dim) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter an integer >= " << minDim << ", dumbass. Try again:\n";
            }
        }
    } else {
        in.dim = minDim;
    }

    in.params.resize(minDim);
}

void setupConsts(struct Input &in) {
    if (in.space == 3.3) {
        in.consts.resize(1);
        in.consts[0].name = "a";
        in.consts[0].closed = {0, 0};
        in.consts[0].bounds = {0, INFINITY};
    }
}

void setupParams(struct Input &in) {
    in.riemCurveSign = 0;

    if (in.space == 1.0) {
        for (int i = 0; i < in.dim; i++) {
            in.params[i].name = "x" + std::to_string(i + 1);
            real(in.params[i]);
        }
    } else if (in.space == 2.0) {
        in.params[0].name = "r";
        in.params[1].name = "theta";

        nonNeg(in.params[0]);
        azimuth(in.params[1]);
    } else if (in.space == 3.1) {
        in.params[0].name = "r";
        in.params[1].name = "theta";
        in.params[2].name = "z";

        nonNeg(in.params[0]);
        azimuth(in.params[1]);
        nonNeg(in.params[2]);
    } else if (in.space == 3.2) {
        in.params[0].name = "r";
        in.params[1].name = "phi";
        in.params[2].name = "theta";

        nonNeg(in.params[0]);
        zenith(in.params[1]);
        azimuth(in.params[2]);
    } else if (in.space == 3.3) {
        in.params[0].name = "r";
        in.params[1].name = "phi";
        in.params[2].name = "theta";

        nonNeg(in.params[0]);
        zenith(in.params[1]);
        azimuth(in.params[2]);
    } else if (in.space == 4.1) {
        in.params[0].name = "r";
        in.params[in.dim - 2].name = "theta";
        in.params[in.dim - 1].name = "z";

        nonNeg(in.params[0]);
        azimuth(in.params[in.dim - 2]);
        nonNeg(in.params[in.dim - 1]);

        for (int i = 1; i < in.dim - 2; i++) {
            in.params[i].name = "phi" + std::to_string(i);
            zenith(in.params[i]);
        }
    } else if (in.space == 4.2) {
        in.params[0].name = "r";
        in.params[in.dim - 1].name = "theta";

        nonNeg(in.params[0]);
        azimuth(in.params[in.dim - 1]);

        for (int i = 1; i < in.dim - 1; i++) {
            in.params[i].name = "phi" + std::to_string(i);
            zenith(in.params[i]);
        }
    }
}

void setupPoints(struct Input &in) {
    if (in.consts.size()) {
        readConsts(in.consts);
        while (!validValues(in.consts));
    }

    for (int i = 0; i < 2; i++) {
        std::cout << "Enter point " << i + 1 << " in the form ";
        readParams(in.params);
        while (!validValues(in.params));
        in.points.push_back(readPoint(in.params));
    }
}
