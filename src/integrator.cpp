#include "../include/integrator.h"
#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <iomanip>

namespace numerical {

Integrator::Integrator(const Input& input, const Function& function)
    : input(input), function(function), result(0.0) {
}

double Integrator::calculateStepSize() const {
    return (input.getUpperBound() - input.getLowerBound()) / input.getIntervals();
}

void Integrator::generatePoints() {
    double h = calculateStepSize();
    int n = input.getIntervals();
    double a = input.getLowerBound();
    
    xValues.resize(n + 1);
    yValues.resize(n + 1);
    
    for (int i = 0; i <= n; ++i) {
        xValues[i] = a + i * h;
        try {
            yValues[i] = function.evaluate(xValues[i]);
        } catch (const std::exception& e) {
            std::cerr << "Error evaluating function at x = " << xValues[i] 
                      << ": " << e.what() << std::endl;
            yValues[i] = 0.0; // Set to 0 on error
        }
    }
}

void Integrator::displayIntermediateValues() const {
    std::cout << "\nStep size h = " << calculateStepSize() << std::endl;
    std::cout << std::setw(5) << "i" << std::setw(15) << "x_i" 
              << std::setw(15) << "f(x_i)" << std::endl;
    std::cout << std::string(35, '-') << std::endl;
    
    for (size_t i = 0; i < xValues.size(); ++i) {
        std::cout << std::setw(5) << i 
                  << std::setw(15) << utils::formatNumber(xValues[i], 6)
                  << std::setw(15) << utils::formatNumber(yValues[i], 6) 
                  << std::endl;
        
        // Add a small delay for better visualization
        if (i % 5 == 4) {
            utils::sleep(100);
        }
    }
    std::cout << std::endl;
}

double Integrator::getResult() const {
    return result;
}

bool Integrator::saveResultToFile(const std::string& filename) const {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        file << "# Numerical Integration Results\n";
        file << "Method: " << getMethodName() << "\n";
        file << "Function: " << function.getDescription() << "\n";
        file << "LowerBound: " << input.getLowerBound() << "\n";
        file << "UpperBound: " << input.getUpperBound() << "\n";
        file << "Intervals: " << input.getIntervals() << "\n";
        file << "Result: " << result << "\n";
        file << "# Created: " << utils::getTimestamp() << "\n\n";
        
        // Save intermediate values
        file << "# Intermediate Values\n";
        file << "i,x_i,f(x_i)\n";
        for (size_t i = 0; i < xValues.size(); ++i) {
            file << i << "," << xValues[i] << "," << yValues[i] << "\n";
        }
        
        file.close();
        return true;
    } catch (...) {
        return false;
    }
}

} // namespace numerical