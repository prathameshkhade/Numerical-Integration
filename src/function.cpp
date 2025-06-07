#include "../include/function.h"
#include <cmath>
#include <stdexcept>

namespace numerical {

// Mathematical constants
constexpr double PI = 3.14159265358979323846;
constexpr double E = 2.71828182845904523536;

Function::Function(int choice) {
    // Define available functions
    switch (choice) {
        case 1: // 1/(1+x)
            func = [](double x) { return 1.0 / (1.0 + x); };
            description = "f(x) = 1/(1+x)";
            break;
        case 2: // x²
            func = [](double x) { return x * x; };
            description = "f(x) = x²";
            break;
        case 3: // sin(x)
            func = [](double x) { return std::sin(x); };
            description = "f(x) = sin(x)";
            break;
        case 4: // e^x
            func = [](double x) { return std::exp(x); };
            description = "f(x) = e^x";
            break;
        case 5: // 1/sqrt(1-x²)
            func = [](double x) { 
                if (x <= -1.0 || x >= 1.0) {
                    throw std::domain_error("Function undefined at x = " + std::to_string(x));
                }
                return 1.0 / std::sqrt(1.0 - x * x); 
            };
            description = "f(x) = 1/sqrt(1-x²)";
            break;
        case 6: // ln(x)
            func = [](double x) { 
                if (x <= 0.0) {
                    throw std::domain_error("Function undefined at x = " + std::to_string(x));
                }
                return std::log(x); 
            };
            description = "f(x) = ln(x)";
            break;
        case 7: // x*sin(x)
            func = [](double x) { return x * std::sin(x); };
            description = "f(x) = x*sin(x)";
            break;
        case 8: // sqrt(x)
            func = [](double x) { 
                if (x < 0.0) {
                    throw std::domain_error("Function undefined at x = " + std::to_string(x));
                }
                return std::sqrt(x); 
            };
            description = "f(x) = sqrt(x)";
            break;
        default:
            // Default to 1/(1+x) if invalid choice
            func = [](double x) { return 1.0 / (1.0 + x); };
            description = "f(x) = 1/(1+x)";
    }
}

double Function::evaluate(double x) const {
    return func(x);
}

std::string Function::getDescription() const {
    return description;
}

std::vector<std::string> Function::getAvailableFunctions() {
    return {
        "1/(1+x)",
        "x²",
        "sin(x)",
        "e^x",
        "1/sqrt(1-x²)",
        "ln(x)",
        "x*sin(x)",
        "sqrt(x)"
    };
}

} // namespace numerical