#include "../../include/methods/romberg.h"
#include "../../include/utils.h"
#include <iostream>
#include <iomanip>
#include <cmath>

namespace numerical {

RombergIntegration::RombergIntegration(const Input& input, const Function& function, int order)
    : Integrator(input, function), order(order) {
    // Ensure order is valid
    if (order < 1) {
        this->order = 1;
    } else if (order > 10) {
        this->order = 10; // Limit maximum order for performance
    }
}

double RombergIntegration::calculate(bool showSteps) {
    // Initialize Romberg table
    R.resize(order + 1, std::vector<double>(order + 1, 0.0));
    
    double h = input.getUpperBound() - input.getLowerBound();
    double a = input.getLowerBound();
    double b = input.getUpperBound();
    
    // Initial trapezoidal approximation with h = b-a
    R[0][0] = (h / 2) * (function.evaluate(a) + function.evaluate(b));
    
    if (showSteps) {
        std::cout << "\nPerforming Romberg Integration" << std::endl;
        std::cout << "Order: " << order << std::endl;
        std::cout << "Initial step size h = " << h << std::endl;
        std::cout << "R[0][0] = " << R[0][0] << " (Trapezoidal rule with 1 interval)" << std::endl;
        utils::sleep(300);
    }
    
    // Fill the Romberg table
    for (int i = 1; i <= order; ++i) {
        // Calculate R[i][0] using trapezoidal rule with 2^i intervals
        h /= 2;
        double sum = 0;
        int steps = std::pow(2, i - 1);
        for (int j = 0; j < steps; ++j) {
            double x = a + (2 * j + 1) * h;
            sum += function.evaluate(x);
        }
        R[i][0] = R[i-1][0] / 2 + h * sum;
        
        if (showSteps) {
            std::cout << "R[" << i << "][0] = " << R[i][0] 
                     << " (Trapezoidal rule with " << (1 << i) << " intervals)" << std::endl;
            utils::sleep(200);
        }
        
        // Calculate R[i][j] using Richardson extrapolation
        for (int j = 1; j <= i; ++j) {
            double factor = std::pow(4, j);
            R[i][j] = R[i][j-1] + (R[i][j-1] - R[i-1][j-1]) / (factor - 1);
            
            if (showSteps) {
                std::cout << "R[" << i << "][" << j << "] = " << R[i][j] 
                         << " (Extrapolation with factor " << factor << ")" << std::endl;
                utils::sleep(200);
            }
        }
    }
    
    // The final result is in the lower-right corner of the Romberg table
    result = R[order][order];
    
    if (showSteps) {
        // Display Romberg table
        std::cout << "\nRomberg Table:" << std::endl;
        for (int i = 0; i <= order; ++i) {
            for (int j = 0; j <= i; ++j) {
                std::cout << std::setw(15) << std::setprecision(8) << R[i][j];
            }
            std::cout << std::endl;
        }
        
        std::cout << "\nFinal result: R[" << order << "][" << order << "] = " << result << std::endl;
    }
    
    return result;
}

std::string RombergIntegration::getMethodName() const {
    return "Romberg Integration (Order " + std::to_string(order) + ")";
}

} // namespace numerical