#include "../../include/methods/trapezoidal.h"
#include "../../include/utils.h"
#include <iostream>
#include <iomanip>

namespace numerical {

TrapezoidalRule::TrapezoidalRule(const Input& input, const Function& function)
    : Integrator(input, function) {
}

double TrapezoidalRule::calculate(bool showSteps) {
    // Generate x and y values
    generatePoints();
    
    // Display intermediate values if requested
    if (showSteps) {
        std::cout << "\nPerforming integration using the Trapezoidal Rule" << std::endl;
        displayIntermediateValues();
    }
    
    // Trapezoidal Rule Formula: h/2 * [f(a) + f(b) + 2 * sum(f(x_i))]
    double h = calculateStepSize();
    double sum = yValues[0] + yValues[input.getIntervals()]; // f(a) + f(b)
    double intermediateSum = 0.0;
    
    for (int i = 1; i < input.getIntervals(); ++i) {
        intermediateSum += yValues[i];
    }
    
    if (showSteps) {
        std::cout << "\nApplying Trapezoidal Rule formula: h/2 * [f(a) + f(b) + 2 * sum(f(x_i))]" << std::endl;
        std::cout << "h = " << h << std::endl;
        std::cout << "f(a) + f(b) = " << yValues[0] << " + " << yValues[input.getIntervals()] 
                  << " = " << (yValues[0] + yValues[input.getIntervals()]) << std::endl;
        std::cout << "sum(f(x_i)) for i=1 to " << (input.getIntervals() - 1) 
                  << " = " << intermediateSum << std::endl;
        
        utils::sleep(500);
    }
    
    sum += 2 * intermediateSum;
    result = (h / 2) * sum;
    
    if (showSteps) {
        std::cout << "\nFinal calculation:" << std::endl;
        std::cout << "(" << h << "/2) * (" << (yValues[0] + yValues[input.getIntervals()]) 
                  << " + 2 * " << intermediateSum << ")" << std::endl;
        std::cout << "(" << h << "/2) * (" << (yValues[0] + yValues[input.getIntervals()]) 
                  << " + " << (2 * intermediateSum) << ")" << std::endl;
        std::cout << "(" << h << "/2) * " << sum << std::endl;
        std::cout << "Result = " << result << std::endl;
    }
    
    return result;
}

std::string TrapezoidalRule::getMethodName() const {
    return "Trapezoidal Rule";
}

} // namespace numerical