#include "../../include/methods/boole.h"
#include "../../include/utils.h"
#include <iostream>
#include <iomanip>

namespace numerical {

BooleRule::BooleRule(const Input& input, const Function& function)
    : Integrator(input, function) {
}

double BooleRule::calculate(bool showSteps) {
    // Check if the method is applicable
    if (!isApplicable()) {
        if (showSteps) {
            std::cerr << "\nError: Boole's rule requires a number of intervals divisible by 4." << std::endl;
        }
        return 0.0;
    }
    
    // Generate x and y values
    generatePoints();
    
    // Display intermediate values if requested
    if (showSteps) {
        std::cout << "\nPerforming integration using Boole's Rule" << std::endl;
        displayIntermediateValues();
    }
    
    // Boole's Rule Formula: 4h/90 * [7(f(a) + f(b)) + 32(f(x1) + f(x3) + ...) + 12(f(x2) + f(x6) + ...) + 14(f(x4) + f(x8) + ...)]
    double h = calculateStepSize();
    double endPoints = 7 * (yValues[0] + yValues[input.getIntervals()]);
    double sum1 = 0.0; // Sum of function values at x1, x5, x9, ...
    double sum2 = 0.0; // Sum of function values at x2, x6, x10, ...
    double sum3 = 0.0; // Sum of function values at x3, x7, x11, ...
    double sum4 = 0.0; // Sum of function values at x4, x8, x12, ...
    
    for (int i = 1; i < input.getIntervals(); ++i) {
        int mod4 = i % 4;
        if (mod4 == 1) {
            sum1 += yValues[i];
        } else if (mod4 == 2) {
            sum2 += yValues[i];
        } else if (mod4 == 3) {
            sum3 += yValues[i];
        } else if (mod4 == 0) {
            sum4 += yValues[i];
        }
    }
    
    if (showSteps) {
        std::cout << "\nApplying Boole's Rule formula: 4h/90 * [7(f(a) + f(b)) + 32(sum1 + sum3) + 12(sum2) + 14(sum4)]" << std::endl;
        std::cout << "h = " << h << std::endl;
        std::cout << "7(f(a) + f(b)) = 7 * (" << yValues[0] << " + " << yValues[input.getIntervals()] 
                  << ") = " << endPoints << std::endl;
        std::cout << "sum1 (indices of form 4k+1) = " << sum1 << std::endl;
        std::cout << "sum2 (indices of form 4k+2) = " << sum2 << std::endl;
        std::cout << "sum3 (indices of form 4k+3) = " << sum3 << std::endl;
        std::cout << "sum4 (indices of form 4k) = " << sum4 << std::endl;
        
        utils::sleep(500);
    }
    
    double sum = endPoints + 32 * (sum1 + sum3) + 12 * sum2 + 14 * sum4;
    result = (4 * h / 90) * sum;
    
    if (showSteps) {
        std::cout << "\nFinal calculation:" << std::endl;
        std::cout << "(4 * " << h << "/90) * (" << endPoints 
                  << " + 32 * (" << sum1 << " + " << sum3 << ")"
                  << " + 12 * " << sum2
                  << " + 14 * " << sum4 << ")" << std::endl;
        std::cout << "(4 * " << h << "/90) * (" << endPoints 
                  << " + " << (32 * (sum1 + sum3))
                  << " + " << (12 * sum2)
                  << " + " << (14 * sum4) << ")" << std::endl;
        std::cout << "(4 * " << h << "/90) * " << sum << std::endl;
        std::cout << "Result = " << result << std::endl;
    }
    
    return result;
}

std::string BooleRule::getMethodName() const {
    return "Boole's Rule";
}

bool BooleRule::isApplicable() const {
    return input.getIntervals() % 4 == 0;
}

} // namespace numerical