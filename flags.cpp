#include "flags.h"

constexpr double PI = 3.141592653589793;
constexpr double E = 2.718281828459045;

bool validVector(double space, double dim, std::vector<double> &vec) {
    std::string str, elem;

    std::getline(std::cin >> std::ws, str);
    eraseSubstring(str, " ");
    std::stringstream stream(str);

    while (std::getline(stream, elem, ',')) {
        if (!validElement(elem, vec)) {
            std::cout << "Invalid vector, dumbass. Try again:\n";
            return false;
        }
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

bool validElement(std::string &elem, std::vector<double> &vec) {
    bool hasPi = false;
    
    if (!isDouble(elem) && inRadians(elem)) {
        eraseSubstring(elem, "pi");
        eraseSubstring(elem, "PI");
        eraseSubstring(elem, "Pi");
        eraseSubstring(elem, "pI");
        eraseSubstring(elem, "*");

        hasPi = true;
    }

    if (hasPi) {
        if (!elem.empty()) {
            vec.push_back(std::stod(elem)*PI);
        } else {
            vec.push_back(PI);
        }
    } else {
        if (!isDouble(elem)) {
            return false;
        }
        vec.push_back(std::stod(elem));
    }

    return true;
}

bool isDouble(std::string elem) {
    try {
        size_t valid = 0;
        std::stod(elem, &valid);
        return (valid == elem.length());
    }
    catch (std::invalid_argument) {
        return false;
    }
    catch (std::out_of_range) {
        return false;
    }
}

bool hasSubstring(std::string &str, std::string substr) {
    return (str.find(substr) != std::string::npos);
}

void eraseSubstring(std::string &str, std::string substr) {
    if (substr.empty()) {
        return;
    }

    size_t idx = 0;

    while ((idx = str.find(substr)) != std::string::npos) {
        str.erase(idx, substr.length());
    }
}

bool inRadians(std::string elem) {
    if (elem == "pi" || elem == "PI" || elem == "Pi" || elem == "pI") {
        return true;        
    }

    try {
        size_t valid = 0;
        std::stod(elem, &valid);
        return (
            (valid == elem.length() - 2 || valid == elem.length() - 3) &&
            (hasSubstring(elem, "pi") || hasSubstring(elem, "PI") ||
             hasSubstring(elem, "Pi") || hasSubstring(elem, "pI"))
        );
    }
    catch (std::invalid_argument) {
        return false;
    }
    catch (std::out_of_range) {
        return false;
    }
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

bool isInteger(double a) {
    return (std::floor(a) == a);
}

bool validRadius(double r) {
    if (r < 0) {
        std::cout << "r must be non-negative, dumbass. Try again:\n";
        return false;
    }

    return true;
}

bool validZenith(double phi, int i) {
    if (phi < 0 || phi > PI) {
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
    if (theta < 0 || theta >= 2*PI) {
        std::cout << "theta is not in [0, 2*PI), dumbass. Try again:\n";
        return false;
    }

    return true;
}
