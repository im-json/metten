#include "value.h"

void readConsts(std::vector<Value> &consts) {
    std::cout << "Enter constants in the form ";

    for (int i = 0; i < consts.size(); i++) {
        std::cout << consts[i].name;
        if (i + 1 < consts.size()) {
            std::cout << ",";
        }
    }

    std::cout << ":\n";
}

void readParams(std::vector<Value> &params) {
    bool hasAzimuth = false, hasZenith = false;

    for (int i = 0; i < params.size(); i++) {
        std::cout << params[i].name;
        if (params[i].name == "theta" || params[i].name == "theta1") {
            hasAzimuth = true;
        }
        if (params[i].name == "phi" || params[i].name == "phi1") {
            hasZenith = true;
        }
        if (i + 1 < params.size()) {
            std::cout << ",";
        }
    }

    if (hasAzimuth) {
        std::cout << ". Use radians for theta ";
    }
    
    if (hasZenith) {
        std::cout << "and phi ";
    }

    std::cout << "(e.g. 2*PI):\n";
}

Eigen::VectorXd readPoint(std::vector<Value> &params) {
    Eigen::VectorXd point(params.size());

    for (int i = 0; i < params.size(); i++) {
        point(i) = (params[i].val);
    }

    return Eigen::Map<Eigen::VectorXd>(point.data(), point.size());
}

bool validValues(std::vector<Value> &vals) {
    std::string str, elem;
    double val;

    std::getline(std::cin >> std::ws, str);
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
    std::stringstream stream(str);

    Calculator<double> calc;

    int idx = 0;

    while (std::getline(stream, elem, ',')) {
        if (idx > vals.size() - 1) {
            std::cout << "Vector dimension is too high, dumbass. Try again:\n";
            return false;
        }

        try {
            val = calc.parse(elem);
            // std::cout << "val: " << val << std::endl;
        }
        catch(const std::runtime_error &e) {
            std::cout << elem << " is invalid syntax, dumbass. Try again:\n";
            return false;
        }
        catch(const std::exception &e) {
            std::cout << elem << " is invalid syntax, dumbass. Try again:\n";
            return false;
        }

        vals[idx].val = val;

        if (!inDomain(vals[idx])) {
            return false;
        }

        idx++;
    }

    if (idx < vals.size()) {
        std::cout << "Vector dimension is too low, dumbass. Try again:\n";
        return false;
    }

    return true;
}

void printPi(double val) {
    if (val && std::floor(val / M_PI) == val / M_PI) {
        if (val != M_PI) {
            std::cout << val / M_PI << "*";
        }
        std::cout << "PI";
    } else {
        std::cout << val;
    }
}

bool inDomain(struct Value &v) {
    if (v.closed[0] && v.val < v.bounds[0]) {
        std::cout << v.name << " can't be < ";
        printPi(v.bounds[0]);
        std::cout << ", dumbass. Try again:\n";
        return false;
    } else if (!v.closed[0] && v.val <= v.bounds[0]) {
        std::cout << v.name << " can't be <= ";
        printPi(v.bounds[0]);
        std::cout << ", dumbass. Try again:\n";
        return false;
    } else if (v.closed[1] && v.val > v.bounds[1]) {
        std::cout << v.name << " can't be > ";
        printPi(v.bounds[1]);
        std::cout << ", dumbass. Try again:\n";
        return false;
    } else if (!v.closed[1] && v.val >= v.bounds[1]) {
        std::cout << v.name << " can't be >= ";
        printPi(v.bounds[1]);
        std::cout << ", dumbass. Try again:\n";
        return false;
    }

    return true;
}

void real(struct Value &v, std::string name) {
    v.name = name;
    v.closed = {0, 0};
    v.bounds = {-INFINITY, INFINITY};
}

void positive(struct Value &v, std::string name) {
    v.name = name;
    v.closed = {0, 0};
    v.bounds = {0, INFINITY};
}

void nonNeg(struct Value &v, std::string name) {
    v.name = name;
    v.closed = {1, 0};
    v.bounds = {0, INFINITY};
}

void zenith(struct Value &v, std::string name) {
    v.name = name;
    v.closed = {1, 1};
    v.bounds = {0, M_PI};
}

void azimuth(struct Value &v, std::string name) {
    v.name = name;
    v.closed = {1, 0};
    v.bounds = {0, 2*M_PI};
}
