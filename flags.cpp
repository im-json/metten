#include "flags.h"

constexpr double PI = 3.141592653589793;
constexpr double E = 2.718281828459045;

bool isValid(int space, int dim, std::vector<double> &vec) {
    std::string str, elem;

    std::getline(std::cin >> std::ws, str);
    eraseSubstring(str, " ");
    std::stringstream stream(str);

    while (std::getline(stream, elem, ',')) {
        if (!isExpression(elem)) {
            std::cout << "Invalid vector, dumbass. Try again:\n";
            return false;
        }
        vec.push_back(std::stod(elem));
    }

    if (vec.size() < dim) {
        std::cout << "Vector dimension is too low, dumbass. Try again:\n";
        return false;
    } else if (vec.size() > dim) {
        std::cout << "Vector dimension is too high, dumbass. Try again:\n";
        return false;
    }

    if (!inDomain(space, dim, vec)) {
        std::cout << "Vector not in the domain space, dumbass. Try again:\n";
        return false;
    }

    return true;
}

bool isExpression(std::string &elem) {
    if (!isDouble(elem)) {
        if (inRadians(elem)) {
            eraseSubstring(elem, "pi");
            eraseSubstring(elem, "PI");
            eraseSubstring(elem, "Pi");
            eraseSubstring(elem, "pI");
            eraseSubstring(elem, "*");

            if (!elem.empty()) {
                elem = std::to_string(std::stod(elem)*PI);
            } else {
                elem = std::to_string(PI);
            }
        }

        if (!isDouble(elem)) {
            return false;
        }
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

bool inDomain(int space, int dim, std::vector<double> vec) {
    if (space == 2) {
        if (vec[0] < 0) {
            std::cout << "r must be non-negative, dumbass" << std::endl;
            return false;
        }
        if (vec[1] < 0 || vec[1] >= 2*PI) {
            std::cout << "phi is not in [0, 2*PI), dumbass" << std::endl;
            return false;
        }
    } else if (space == 3) {
        if (vec[0] < 0) {
            std::cout << "r must be non-negative, dumbass" << std::endl;
            return false;
        }

        for (int i = 1; i < dim - 1; i++) {
            if (vec[i] < 0 || vec[i] > PI) {
                std::cout << "theta" << i << " is not in [0, PI], dumbass" << std::endl;
                return false;
            }
        }

        if (vec[dim - 1] < 0 || vec[dim - 1] >= 2*PI) {
            std::cout << "phi is not in [0, 2*PI), dumbass" << std::endl;
            return false;
        }
    }

    return true;
}