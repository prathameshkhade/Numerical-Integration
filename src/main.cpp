#include "../include/function.h"
#include "../include/input.h"
#include "../include/methods/trapezoidal.h"
#include "../include/methods/simpson13.h"
#include "../include/methods/simpson38.h"
#include "../include/methods/boole.h"
#include "../include/methods/romberg.h"
#include "../include/utils.h"
#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

using namespace numerical;

// Function declarations
void runIntegration();
void compareAllMethods();
void loadPreviousResult();
void showHelp();
void showAbout();

int main() {
    // Display welcome message
    std::cout << "=====================================================\n";
    std::cout << "          NUMERICAL INTEGRATION CALCULATOR          \n";
    std::cout << "=====================================================\n";
    std::cout << "Author: Prathamesh Khade\n";
    std::cout << "Version: 2.0\n\n";
    
    bool exitProgram = false;
    
    while (!exitProgram) {
        // Main menu
        std::vector<std::string> mainOptions = {
            "Perform integration",
            "Compare all integration methods",
            "Load previous results",
            "Help",
            "About",
            "Exit"
        };
        
        int choice = utils::getMenuChoice("Main Menu", mainOptions);
        
        switch (choice) {
            case 1:
                runIntegration();
                break;
            case 2:
                compareAllMethods();
                break;
            case 3:
                loadPreviousResult();
                break;
            case 4:
                showHelp();
                break;
            case 5:
                showAbout();
                break;
            case 6:
                exitProgram = true;
                break;
        }
    }
    
    std::cout << "\nThank you for using the Numerical Integration Calculator!\n";
    return 0;
}

void runIntegration() {
    utils::clearScreen();
    std::cout << "Perform Integration\n";
    std::cout << "====================\n\n";
    
    // Get user input for the integration parameters
    Input input;
    Function function(input.getFunctionChoice());
    
    // Display input parameters
    std::cout << "\nIntegration Parameters:\n";
    input.display();
    
    // Select integration method
    std::vector<std::string> methodOptions = {
        "Trapezoidal Rule",
        "Simpson's 1/3 Rule",
        "Simpson's 3/8 Rule",
        "Boole's Rule",
        "Romberg Integration",
        "Back to Main Menu"
    };
    
    int methodChoice = utils::getMenuChoice("Select Integration Method", methodOptions);
    
    if (methodChoice == 6) {
        return; // Return to main menu
    }
    
    // Create the appropriate integrator
    std::unique_ptr<Integrator> integrator;
    
    switch (methodChoice) {
        case 1:
            integrator = std::make_unique<TrapezoidalRule>(input, function);
            break;
        case 2:
            integrator = std::make_unique<SimpsonOneThird>(input, function);
            break;
        case 3:
            integrator = std::make_unique<SimpsonThreeEighth>(input, function);
            break;
        case 4:
            integrator = std::make_unique<BooleRule>(input, function);
            break;
        case 5: {
            int order = 4; // Default order
            std::cout << "Enter the order for Romberg integration (1-10): ";
            std::cin >> order;
            if (order < 1 || order > 10) {
                order = 4;
                std::cout << "Invalid order. Using default order of 4." << std::endl;
            }
            integrator = std::make_unique<RombergIntegration>(input, function, order);
            break;
        }
    }
    
    // Perform integration
    utils::clearScreen();
    std::cout << "Calculating using " << integrator->getMethodName() << "...\n\n";
    
    bool showSteps = true;
    std::cout << "Show calculation steps? (1=Yes, 0=No): ";
    std::cin >> showSteps;
    
    double result = integrator->calculate(showSteps);
    
    // Display the result
    std::cout << "\n===========================================\n";
    std::cout << "Integration of " << function.getDescription() << "\n";
    std::cout << "from " << input.getLowerBound() << " to " << input.getUpperBound() << "\n";
    std::cout << "using " << integrator->getMethodName() << ":\n\n";
    std::cout << "Result = " << result << "\n";
    std::cout << "===========================================\n";
    
    // Save result to file
    std::cout << "\nDo you want to save the result to a file? (1=Yes, 0=No): ";
    bool saveToFile;
    std::cin >> saveToFile;
    
    if (saveToFile) {
        std::string filename = "integration_result_" + utils::getTimestamp() + ".txt";
        // Replace spaces and colons in filename
        std::replace(filename.begin(), filename.end(), ' ', '_');
        std::replace(filename.begin(), filename.end(), ':', '-');
        
        if (integrator->saveResultToFile(filename)) {
            std::cout << "Result saved to " << filename << std::endl;
        } else {
            std::cout << "Failed to save result to file." << std::endl;
        }
    }
    
    utils::waitForKeyPress();
}

void compareAllMethods() {
    utils::clearScreen();
    std::cout << "Compare All Integration Methods\n";
    std::cout << "===============================\n\n";
    
    // Get user input for the integration parameters
    Input input;
    Function function(input.getFunctionChoice());
    
    // Display input parameters
    std::cout << "\nIntegration Parameters:\n";
    input.display();
    
    // Create integrators for all methods
    std::vector<std::unique_ptr<Integrator>> integrators;
    integrators.push_back(std::make_unique<TrapezoidalRule>(input, function));
    integrators.push_back(std::make_unique<SimpsonOneThird>(input, function));
    integrators.push_back(std::make_unique<SimpsonThreeEighth>(input, function));
    integrators.push_back(std::make_unique<BooleRule>(input, function));
    integrators.push_back(std::make_unique<RombergIntegration>(input, function, 4));
    
    // Perform calculations
    std::cout << "\nCalculating results using all methods...\n";
    
    std::vector<double> results;
    std::vector<std::string> methodNames;
    
    for (const auto& integrator : integrators) {
        std::cout << "- " << integrator->getMethodName() << "... ";
        double result = integrator->calculate(false);
        results.push_back(result);
        methodNames.push_back(integrator->getMethodName());
        std::cout << "Done\n";
    }
    
    // Display comparison table
    std::cout << "\nComparison of Integration Methods:\n";
    std::cout << "=================================\n\n";
    std::cout << std::left << std::setw(25) << "Method" << std::right << std::setw(20) << "Result" << std::endl;
    std::cout << std::string(45, '-') << std::endl;
    
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << std::left << std::setw(25) << methodNames[i] 
                  << std::right << std::setw(20) << std::fixed << std::setprecision(10) << results[i] << std::endl;
    }
    
    // Find the method with the most accurate result (assuming higher-order methods are more accurate)
    double referenceResult = results.back(); // Romberg Integration result
    std::cout << "\nAssuming Romberg Integration as reference:\n";
    std::cout << std::left << std::setw(25) << "Method" << std::right << std::setw(20) << "Absolute Error" << std::endl;
    std::cout << std::string(45, '-') << std::endl;
    
    for (size_t i = 0; i < results.size() - 1; ++i) {
        double error = std::abs(results[i] - referenceResult);
        std::cout << std::left << std::setw(25) << methodNames[i] 
                  << std::right << std::setw(20) << std::scientific << std::setprecision(6) << error << std::endl;
    }
    
    utils::waitForKeyPress();
}

void loadPreviousResult() {
    utils::clearScreen();
    std::cout << "Load Previous Results\n";
    std::cout << "====================\n\n";
    
    std::cout << "This feature allows you to load previously saved integration results.\n";
    std::cout << "Please enter the filename: ";
    
    std::string filename;
    std::cin.ignore();
    std::getline(std::cin, filename);
    
    if (!utils::fileExists(filename)) {
        std::cout << "Error: File '" << filename << "' does not exist." << std::endl;
        utils::waitForKeyPress();
        return;
    }
    
    // Simple file reader
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "Error: Could not open file." << std::endl;
    }
    
    utils::waitForKeyPress();
}

void showHelp() {
    utils::clearScreen();
    std::cout << "Help & Documentation\n";
    std::cout << "====================\n\n";
    
    std::cout << "Numerical Integration Calculator - Help\n\n";
    
    std::cout << "This program allows you to calculate definite integrals using various\n";
    std::cout << "numerical integration methods.\n\n";
    
    std::cout << "Available Integration Methods:\n";
    std::cout << "1. Trapezoidal Rule: Approximates the integral using linear approximation\n";
    std::cout << "   Formula: h/2 * [f(a) + f(b) + 2 * sum(f(x_i))]\n\n";
    
    std::cout << "2. Simpson's 1/3 Rule: Uses quadratic polynomials for approximation\n";
    std::cout << "   Formula: h/3 * [f(a) + f(b) + 4 * sum(f(x_odd)) + 2 * sum(f(x_even))]\n";
    std::cout << "   Note: Requires an even number of intervals\n\n";
    
    std::cout << "3. Simpson's 3/8 Rule: Uses cubic polynomials for approximation\n";
    std::cout << "   Formula: 3h/8 * [f(a) + f(b) + 3 * sum(f(not divisible by 3)) + 2 * sum(f(divisible by 3))]\n";
    std::cout << "   Note: Requires a number of intervals divisible by 3\n\n";
    
    std::cout << "4. Boole's Rule: Uses fourth-degree polynomials for approximation\n";
    std::cout << "   Formula: 4h/90 * [7(f(a) + f(b)) + 32(f(x1) + f(x3) + ...) + 12(f(x2) + f(x6) + ...) + 14(f(x4) + f(x8) + ...)]\n";
    std::cout << "   Note: Requires a number of intervals divisible by 4\n\n";
    
    std::cout << "5. Romberg Integration: Uses extrapolation to improve accuracy\n";
    std::cout << "   Note: Higher order generally gives more accurate results\n\n";
    
    std::cout << "How to use the program:\n";
    std::cout << "1. Select 'Perform integration' from the main menu\n";
    std::cout << "2. Choose a function from the available options\n";
    std::cout << "3. Enter the lower and upper bounds of integration\n";
    std::cout << "4. Enter the number of intervals\n";
    std::cout << "5. Select an integration method\n";
    std::cout << "6. View the result and intermediate steps\n\n";
    
    std::cout << "You can also compare all integration methods using the 'Compare all methods' option.\n";
    
    utils::waitForKeyPress();
}

void showAbout() {
    utils::clearScreen();
    std::cout << "About\n";
    std::cout << "=====\n\n";
    
    std::cout << "Numerical Integration Calculator\n";
    std::cout << "Version 2.0\n\n";
    
    std::cout << "Author: Prathamesh Khade\n";
    std::cout << "Last updated: 2025-06-07\n\n";
    
    std::cout << "This program implements various numerical integration methods to\n";
    std::cout << "approximate definite integrals. It features a modular, object-oriented\n";
    std::cout << "design and supports multiple integration techniques.\n\n";
    
    std::cout << "Features:\n";
    std::cout << "- Multiple integration methods\n";
    std::cout << "- Step-by-step calculation display\n";
    std::cout << "- Method comparison\n";
    std::cout << "- Result saving and loading\n";
    std::cout << "- Cross-platform compatibility\n\n";
    
    std::cout << "License: MIT License\n";
    
    utils::waitForKeyPress();
}