#include "../../include/methods/simpson13.h"
#include "../../include/utils.h"
#include <iostream>
#include <iomanip>

namespace numerical {

SimpsonOneThird::SimpsonOneThird(const Input& input, const Function& function)
    : Integrator(input, function) {
}

double SimpsonOneThird::calculate(bool showSteps) {
    // Check if the method is applicable
    if (!isApplicable()) {
        if (showSteps) {
            std::cerr << "\nError: Simpson's 1/3 rule requires an even number of intervals." << std::endl;
        }
        return 0.0;
    }
    
    // Generate x and y values
    generatePoints();
    
    // Display intermediate values if requested
    if (showSteps) {
        std::cout << "\nPerforming integration using Simpson's 1/3 Rule" << std::endl;
        displayIntermediateValues();
    }
    
    // Simpson's 1/3 Rule Formula: h/3 * [f(a) + f(b) + 4 * sum(f(x_odd)) + 2 * sum(f(x_even))]
    double h = calculateStepSize();
    double sum = yValues[0] + yValues[input.getIntervals()]; // f(a) + f(b)
    double evenSum = 0.0;
    double oddSum = 0.0;
    
    for (int i = 1; i < input.getIntervals(); ++i) {
        if (i % 2 == 0) {
            evenSum += yValues[i];
        } else {
            oddSum += yValues[i];
        }
    }
    
    if (showSteps) {
        std::cout << "\nApplying Simpson's 1/3 Rule formula: h/3 * [f(a) + f(b) + 4 * sum(f(x_odd)) + 2 * sum(f(x_even))]" << std::endl;
        std::cout << "h = " << h << std::endl;
        std::cout << "f(a) + f(b) = " << yValues[0] << " + " << yValues[input.getIntervals()] 
                  << " = " << (yValues[0] + yValues[input.getIntervals()]) << std::endl;
        std::cout << "sum of f(x) at odd points = " << oddSum << std::endl;
        std::cout << "sum of f(x) at even points = " << evenSum << std::endl;
        
        utils::sleep(500);
    }
    
    sum += 4 * oddSum + 2 * evenSum;
    result = (h / 3) * sum;
    
    if (showSteps) {
        std::cout << "\nFinal calculation:" << std::endl;
        std::cout << "(" << h << "/3) * (" << (yValues[0] + yValues[input.getIntervals()]) 
                  << " + 4 * " << oddSum << " + 2 * " << evenSum << ")" << std::endl;
        std::cout << "(" << h << "/3) * (" << (yValues[0] + yValues[input.getIntervals()]) 
                  << " + " << (4 * oddSum) << " + " << (2 * evenSum) << ")" << std::endl;
        std::cout << "(" << h << "/3) * " << sum << std::endl;
        std::cout << "Result = " << result << std::endl;
    }
    
    return result;
}

std::string SimpsonOneThird::getMethodName() const {
    return "Simpson's 1/3 Rule";
}

bool SimpsonOneThird::isApplicable() const {
    return input.getIntervals() % 2 == 0;
}

} // namespace numerical