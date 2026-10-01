#include "checks.h"

bool validVector(double space, double dim, std::vector<double> constants, std::vector<double> &vec) {
    std::string str, elem;
    double val;

    std::getline(std::cin >> std::ws, str);
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    std::stringstream stream(str);

    Calculator<double> calc;

    while (std::getline(stream, elem, ',')) {
        try {
            val = calc.parse(elem);
            // std::cout << "val: " << val << std::endl;
        }
        catch(const std::runtime_error &e) {
            std::cout << elem << " is invalid, dumbass. Try again:\n";
            return false;
        }
        catch(const std::exception &e) {
            std::cout << elem << " is invalid, dumbass. Try again:\n";
            return false;
        }
        vec.push_back(val);
    }

    if (vec.size() < dim) {
        std::cout << "Vector dimension is too low, dumbass. Try again:\n";
        return false;
    } else if (vec.size() > dim) {
        std::cout << "Vector dimension is too high, dumbass. Try again:\n";
        return false;
    }

    if (!inDomain(space, dim, constants, vec)) {
        return false;
    }

    return true;
}

bool inDomain(double space, double dim, std::vector<double> constants, std::vector<double> vec) {
    if (space == 2.0) {
        if (!validRadius(vec[0])) {
            return false;
        }
        if (!validAzimuth(vec[1], "theta")) {
            return false;
        }
    } else if (space == 3.1) {
        if (!validRadius(vec[0])) {
            return false;
        }
        if (!validAzimuth(vec[1], "theta")) {
            return false;
        }
    } else if (space == 3.2) {
        if (!validRadius(vec[0])) {
            return false;
        }
        if (!validZenith(vec[1], "phi")) {
            return false;
        }
        if (!validAzimuth(vec[2], "theta")) {
            return false;
        }
    }  else if (space == 3.3) {
        if (!validMajorRadius(vec[0], constants[0])) {
            return false;
        }
        if (!validAzimuth(vec[1], "phi")) {
            return false;
        }
        if (!validAzimuth(vec[2], "theta")) {
            return false;
        }
    } else if (space == 4.1) {
        if (!validRadius(vec[0])) {
            return false;
        }
        for (int i = 1; i < dim - 2; i++) {
            if (!validZenith(vec[i], "phi" + std::to_string(i))) {
                return false;
            }
        }
        if (!validAzimuth(vec[dim - 2], "theta")) {
            return false;
        }
    } else if (space == 4.2) {
        if (!validRadius(vec[0])) {
            return false;
        }
        for (int i = 1; i < dim - 1; i++) {
            if (!validZenith(vec[i], "phi" + std::to_string(i))) {
                return false;
            }
        }
        if (!validAzimuth(vec[dim - 1], "theta")) {
            return false;
        }
    }

    return true;
}

bool validRadius(double r) {
    if (r < 0) {
        std::cout << "r must be non-negative, dumbass. Try again:\n";
        return false;
    }

    return true;
}

bool validMajorRadius(double r, double a) {
    if (r <= 0 || r >= a) {
        std::cout << "r is not in (0,a), dumbass. Try again:\n";
        return false;
    }

    return true;
}

bool validZenith(double x, std::string name) {
    if (x < 0 || x > M_PI) {
        std::cout << name << " is not in [0,PI], dumbass. Try again:\n";

        return false;
    }

    return true;
}

bool validAzimuth(double x, std::string name) {
    if (x < 0 || x >= 2*M_PI) {
        std::cout << name << " is not in [0,2*PI), dumbass. Try again:\n";
        return false;
    }

    return true;
}
