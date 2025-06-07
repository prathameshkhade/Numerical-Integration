#include "../include/input.h"
#include "../include/function.h"
#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <limits>

namespace numerical {

Input::Input() {
    // Display available functions and get user choice
    std::vector<std::string> functions = Function::getAvailableFunctions();
    std::cout << "Available functions:" << std::endl;
    for (size_t i = 0; i < functions.size(); ++i) {
        std::cout << (i + 1) << ". " << functions[i] << std::endl;
    }
    
    std::cout << "Select function number: ";
    std::cin >> funcChoice;
    
    // Validate function choice
    while (std::cin.fail() || funcChoice < 1 || funcChoice > static_cast<int>(functions.size())) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and " 
                  << functions.size() << ": ";
        std::cin >> funcChoice;
    }
    
    // Get integration bounds
    std::cout << "Enter lower bound a: ";
    std::cin >> a;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number: ";
        std::cin >> a;
    }
    
    std::cout << "Enter upper bound b: ";
    std::cin >> b;
    while (std::cin.fail() || b <= a) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a number greater than " << a << ": ";
        std::cin >> b;
    }
    
    // Get number of intervals
    std::cout << "Enter number of intervals n: ";
    std::cin >> n;
    while (std::cin.fail() || n < 1) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a positive integer: ";
        std::cin >> n;
    }
}

Input::Input(double lowerBound, double upperBound, int intervals, int functionChoice)
    : a(lowerBound), b(upperBound), n(intervals), funcChoice(functionChoice) {
    // Validate inputs
    if (b <= a) {
        throw std::invalid_argument("Upper bound must be greater than lower bound");
    }
    if (n < 1) {
        throw std::invalid_argument("Number of intervals must be positive");
    }
    if (funcChoice < 1 || funcChoice > static_cast<int>(Function::getAvailableFunctions().size())) {
        throw std::invalid_argument("Invalid function choice");
    }
}

double Input::getLowerBound() const {
    return a;
}

double Input::getUpperBound() const {
    return b;
}

int Input::getIntervals() const {
    return n;
}

int Input::getFunctionChoice() const {
    return funcChoice;
}

void Input::display() const {
    std::cout << "Integration parameters:" << std::endl;
    std::cout << "Function: " << Function(funcChoice).getDescription() << std::endl;
    std::cout << "Lower bound (a): " << a << std::endl;
    std::cout << "Upper bound (b): " << b << std::endl;
    std::cout << "Number of intervals (n): " << n << std::endl;
}

bool Input::saveToFile(const std::string& filename) const {
    try {
        std::ofstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        file << "# Numerical Integration Parameters\n";
        file << "Function: " << Function(funcChoice).getDescription() << "\n";
        file << "LowerBound: " << a << "\n";
        file << "UpperBound: " << b << "\n";
        file << "Intervals: " << n << "\n";
        file << "FunctionChoice: " << funcChoice << "\n";
        file << "# Created: " << utils::getTimestamp() << "\n";
        
        file.close();
        return true;
    } catch (...) {
        return false;
    }
}

bool Input::loadFromFile(const std::string& filename) {
    try {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }
        
        std::string line, key, value;
        while (std::getline(file, line)) {
            // Skip comments and empty lines
            if (line.empty() || line[0] == '#') {
                continue;
            }
            
            // Parse key-value pairs
            size_t pos = line.find(':');
            if (pos != std::string::npos) {
                key = line.substr(0, pos);
                value = line.substr(pos + 1);
                
                // Trim whitespace
                value.erase(0, value.find_first_not_of(" \t"));
                
                if (key == "LowerBound") {
                    a = std::stod(value);
                } else if (key == "UpperBound") {
                    b = std::stod(value);
                } else if (key == "Intervals") {
                    n = std::stoi(value);
                } else if (key == "FunctionChoice") {
                    funcChoice = std::stoi(value);
                }
            }
        }
        
        file.close();
        return true;
    } catch (...) {
        return false;
    }
}

} // namespace numerical