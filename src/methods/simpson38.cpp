#include "../../include/methods/simpson38.h"
#include "../../include/utils.h"
#include <iostream>
#include <iomanip>

namespace numerical {

SimpsonThreeEighth::SimpsonThreeEighth(const Input& input, const Function& function)
    : Integrator(input, function) {
}

double SimpsonThreeEighth::calculate(bool showSteps) {
    // Check if the method is applicable
    if (!isApplicable()) {
        if (showSteps) {
            std::cerr << "\nError: Simpson's 3/8 rule requires a number of intervals divisible by 3." << std::endl;
        }
        return 0.0;
    }
    
    // Generate x and y values
    generatePoints();
    
    // Display intermediate values if requested
    if (showSteps) {
        std::cout << "\nPerforming integration using Simpson's 3/8 Rule" << std::endl;
        displayIntermediateValues();
    }
    
    // Simpson's 3/8 Rule Formula: 3h/8 * [f(a) + f(b) + 3 * sum(f(not divisible by 3)) + 2 * sum(f(divisible by 3))]
    double h = calculateStepSize();
    double sum = yValues[0] + yValues[input.getIntervals()]; // f(a) + f(b)
    double sumMultiple3 = 0.0;
    double sumNotMultiple3 = 0.0;
    
    for (int i = 1; i < input.getIntervals(); ++i) {
        if (i % 3 == 0) {
            sumMultiple3 += yValues[i];
        } else {
            sumNotMultiple3 += yValues[i];
        }
    }
    
    if (showSteps) {
        std::cout << "\nApplying Simpson's 3/8 Rule formula: 3h/8 * [f(a) + f(b) + 3 * sum(f(not divisible by 3)) + 2 * sum(f(divisible by 3))]" << std::endl;
        std::cout << "h = " << h << std::endl;
        std::cout << "f(a) + f(b) = " << yValues[0] << " + " << yValues[input.getIntervals()] 
                  << " = " << (yValues[0] + yValues[input.getIntervals()]) << std::endl;
        std::cout << "sum of f(x) at indices divisible by 3 = " << sumMultiple3 << std::endl;
        std::cout << "sum of f(x) at indices not divisible by 3 = " << sumNotMultiple3 << std::endl;
        
        utils::sleep(500);
    }
    
    sum += 2 * sumMultiple3 + 3 * sumNotMultiple3;
    result = (3 * h / 8) * sum;
    
    if (showSteps) {
        std::cout << "\nFinal calculation:" << std::endl;
        std::cout << "(3 * " << h << "/8) * (" << (yValues[0] + yValues[input.getIntervals()]) 
                  << " + 2 * " << sumMultiple3 << " + 3 * " << sumNotMultiple3 << ")" << std::endl;
        std::cout << "(3 * " << h << "/8) * (" << (yValues[0] + yValues[input.getIntervals()]) 
                  << " + " << (2 * sumMultiple3) << " + " << (3 * sumNotMultiple3) << ")" << std::endl;
        std::cout << "(3 * " << h << "/8) * " << sum << std::endl;
        std::cout << "Result = " << result << std::endl;
    }
    
    return result;
}

std::string SimpsonThreeEighth::getMethodName() const {
    return "Simpson's 3/8 Rule";
}

bool SimpsonThreeEighth::isApplicable() const {
    return input.getIntervals() % 3 == 0;
}

} // namespace numerical