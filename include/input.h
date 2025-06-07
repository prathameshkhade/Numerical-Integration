#ifndef INPUT_H
#define INPUT_H

#include <string>

namespace numerical {

/**
 * @class Input
 * @brief Handles user input for integration parameters
 * 
 * This class manages the input of integration boundaries, interval count,
 * and function selection.
 */
class Input {
public:
    /**
     * @brief Default constructor that prompts for input
     */
    Input();

    /**
     * @brief Parameterized constructor
     * @param lowerBound Lower bound of integration
     * @param upperBound Upper bound of integration
     * @param intervals Number of intervals for integration
     * @param functionChoice Index of function to integrate
     */
    Input(double lowerBound, double upperBound, int intervals, int functionChoice);

    /**
     * @brief Get the lower bound of integration
     * @return The lower bound
     */
    double getLowerBound() const;

    /**
     * @brief Get the upper bound of integration
     * @return The upper bound
     */
    double getUpperBound() const;

    /**
     * @brief Get the number of intervals
     * @return The number of intervals
     */
    int getIntervals() const;

    /**
     * @brief Get the function choice index
     * @return The function choice index
     */
    int getFunctionChoice() const;

    /**
     * @brief Display the current input parameters
     */
    void display() const;

    /**
     * @brief Save input parameters to a file
     * @param filename The name of the file to save to
     * @return True if successful, false otherwise
     */
    bool saveToFile(const std::string& filename) const;

    /**
     * @brief Load input parameters from a file
     * @param filename The name of the file to load from
     * @return True if successful, false otherwise
     */
    bool loadFromFile(const std::string& filename);

private:
    double a;         // Lower bound of integration
    double b;         // Upper bound of integration
    int n;            // Number of intervals
    int funcChoice;   // Function choice index
};

} // namespace numerical

#endif // INPUT_H