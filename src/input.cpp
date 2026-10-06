#include "input.h"

struct Input setup() {
    struct Input in;

    in.space = 0.0;
    in.dim = 0.0;
    in.consts.resize(0);

    setupSpace(in);
    setupRegion(in);
    setupCoords(in);
    setupConsts(in);
    setupParams(in);
    setupPoints(in);

    return in;
}

void setupSpace(struct Input &in) {
    std::string spaces = "RST";

    std::string str = " ";

    while (spaces.find(str) == std::string::npos || str.size() != 1) {
        std::cout << "Select a space:\n";
        std::cout << "Type 'R' for real\nType 'S' for sphere\n";
        std::cout << "Type 'T' for torus\n";
        std::cin >> str;
        if (spaces.find(str) == std::string::npos || str.size() != 1) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid capital letter, dumbass. Try again:\n";
        }
    }

    in.space = str;
}

void promptReal() {
    std::cout << "Select a region:\n";
    std::cout << "Type '1' for cartesian (R^n)\nType '2' for polar (R^2)\n";
    std::cout << "Type '3' for solid cylinder (R^3)\nType '4' for solid ball (R^3)\n";
    std::cout << "Type '4' for solid ball (R^3)\nType '5' for solid torus (R^3)\n";
    std::cout << "Type '6' for solid hypercylinder (R^n)\n";
    std::cout << "Type '7' for solid hyperball (R^n)\n";
}

void promptSphere() {
    std::cout << "Select a region:\n";
    std::cout << "Type '1' for sphere (S^2)\nType '2' for hypersphere (S^n)\n";
}

void promptTorus() {
    std::cout << "Select a region:\n";
    std::cout << "Type '1' for torus (T^2)\nType '2' for hypertorus (T^n)"; 
}

void setupRegion(struct Input &in) {
    double region = 0.0, last = 0.0;

    while (region < 1.0 || region > last || std::floor(region) != region) {
        if (in.space == "R") {
            promptReal();
            last = 7.0;
        } else if (in.space == "S") {
            promptSphere();
            last = 2.0;
        } else if (in.space == "T") {
            promptTorus();
            last = 2.0;
        }

        std::cin >> region;

        if (region < 1.0 || region > last || std::floor(region) != region) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a valid number, dumbass. Try again:\n";
        }
    }

    if ((in.space == "R" && region == 2.0) ||
        ((in.space == "S" || in.space == "T") && region == 1.0)) {
        in.dim = 2;
    } else if (in.space == "R" && (region == 3.0 || region == 4.0 || region == 5.0)) {
        in.dim = 3;
    } else {
        setupDim(in);
    }

    in.region = region;
}

void setupDim(struct Input &in) {
    double dim = 0.0;

    while (dim < 3.0 || std::floor(dim) != dim) {
        std::cout << "Enter dimension:\n";
        std::cin >> dim;
        if (dim < 3.0 || std::floor(dim) != dim) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter an integer >= 3, dumbass. Try again:\n";
        }
    }

    in.dim = static_cast<int>(dim);
}

void setupCoords(struct Input &in) {
    if (in.space == "R" && in.region <= 1.0) {
        in.coords = Coords::Cartesian;
    } else if ((in.space == "R" && in.region > 1.0 && in.region <= 7.0) ||
                in.space == "S") {
        in.coords = Coords::Spherical;
    }  else if (in.space == "T") {
        in.coords = Coords::Toroidal;
    }
}

void setupConsts(struct Input &in) {
    if (in.space == "R" && in.region == 5.0) {
        in.consts.resize(1);
        positive(in.consts[0], "a");
    } else if ((in.space == "S" || in.space == "T") && in.region == 1.0) {
        in.consts.resize(1);
        positive(in.consts[0], "r");
    }
}

void setupParams(struct Input &in) {
    in.riemCurveSign = 0;
    in.params.resize(in.dim);

    if (in.coords == Coords::Cartesian) {
        for (int i = 0; i < in.dim; i++) {
            real(in.params[i], "x" + std::to_string(i + 1));
        }
    } else if (in.coords == Coords::Spherical) {
        nonNeg(in.params[0], "r");
    }

    if (in.space == "R") {
        if (in.coords == Coords::Cartesian) {
            for (int i = 0; i < in.dim; i++) {
                real(in.params[i], "x" + std::to_string(i + 1));
            }
        } else if (in.coords == Coords::Spherical) {
            nonNeg(in.params[0], "r");
        }
        
        if (in.region == 2.0) {
            azimuth(in.params[1], "theta");
        } else if (in.region == 3.0) {
            azimuth(in.params[1], "theta");
            nonNeg(in.params[2], "z");
        } else if (in.region == 4.0 || in.region == 5.0) {
            zenith(in.params[1], "phi");
            azimuth(in.params[2], "theta");
        } else if (in.region == 6.0) {
            azimuth(in.params[in.dim - 2], "theta");
            nonNeg(in.params[in.dim - 1], "z");
            for (int i = 1; i < in.dim - 2; i++) {
                zenith(in.params[i], "phi" + std::to_string(i));
            }
        } else if (in.region == 7.0) {
            azimuth(in.params[in.dim - 1], "theta");
            for (int i = 1; i < in.dim - 1; i++) {
                zenith(in.params[i], "phi" + std::to_string(i));
            }
        }
    } else if (in.space == "S") {
        if (in.region == 1.0) {
            zenith(in.params[0], "phi");
            azimuth(in.params[1], "theta");
        } else if (in.region == 2.0) {
            azimuth(in.params[in.dim - 1], "theta");
            for (int i = 0; i < in.dim - 1; i++) {
                zenith(in.params[i], "phi" + std::to_string(i));
            }
        }
    } else if (in.space == "T") {
        if (in.region == 1.0) {
            return;
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
