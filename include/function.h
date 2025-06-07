#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include <string>
#include <vector>

namespace numerical {

/**
 * @class Function
 * @brief Represents a mathematical function for numerical integration
 * 
 * This class allows users to select from predefined functions or
 * create custom functions for numerical integration.
 */
class Function {
public:
    /**
     * @brief Constructor for predefined functions
     * @param choice The index of the predefined function to use
     */
    explicit Function(int choice);

    /**
     * @brief Evaluates the function at a given point
     * @param x The point at which to evaluate the function
     * @return The function value at the given point
     */
    double evaluate(double x) const;
    
    /**
     * @brief Get the function's description for display
     * @return The function description as a string
     */
    std::string getDescription() const;
    
    /**
     * @brief Get the list of available predefined functions
     * @return Vector of function descriptions
     */
    static std::vector<std::string> getAvailableFunctions();

private:
    std::function<double(double)> func; // Function to evaluate
    std::string description;            // Function description
};

} // namespace numerical

#endif // FUNCTION_H