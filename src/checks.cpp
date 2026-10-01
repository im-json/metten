#include "checks.h"

bool validVector(double space, double dim, std::vector<double> &vec) {
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

    if (!inDomain(space, dim, vec)) {
        return false;
    }

    return true;
}

bool inDomain(double space, double dim, std::vector<double> vec) {
    if (space == 2.0) {
        if (!validRadius(vec[0]) | !validAzimuth(vec[1])) {
            return false;
        }
    } else if (space == 3.1) {
        if (!validRadius(vec[0]) | !validAzimuth(vec[1])) {
            return false;
        }
    } else if (space == 3.2) {
        if (!validRadius(vec[0]) | !validZenith(vec[1], 0) | !validAzimuth(vec[2])) {
            return false;
        }
    } else if (space == 4.1) {
        if (!validRadius(vec[0]) | !validAzimuth(vec[dim - 2])) {
            return false;
        }

        for (int i = 1; i < dim - 2; i++) {
            if (!validZenith(vec[i], i)) {
                return false;
            }
        }
    } else if (space == 4.2) {
        if (!validRadius(vec[0]) | !validAzimuth(vec[dim - 1])) {
            return false;
        }

        for (int i = 1; i < dim - 1; i++) {
            if (!validZenith(vec[i], i)) {
                return false;
            }
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

bool validZenith(double phi, int i) {
    if (phi < 0 || phi > M_PI) {
        if (!i) {
            std::cout << "phi is not in [0, PI], dumbass. Try again:\n";
        } else {
            std::cout << "phi" << i << " is not in [0, PI], dumbass. Try again:\n";
        }
        return false;
    }

    return true;
}

bool validAzimuth(double theta) {
    if (theta < 0 || theta >= 2*M_PI) {
        std::cout << "theta is not in [0, 2*PI), dumbass. Try again:\n";
        return false;
    }

    return true;
}
