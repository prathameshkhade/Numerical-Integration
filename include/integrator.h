#ifndef INTEGRATOR_H
#define INTEGRATOR_H

#include "function.h"
#include "input.h"
#include <string>
#include <vector>

namespace numerical {

/**
 * @class Integrator
 * @brief Base class for numerical integration methods
 * 
 * This abstract class defines the interface for all numerical
 * integration methods.
 */
class Integrator {
public:
    /**
     * @brief Constructor
     * @param input Parameters for integration
     * @param function Function to integrate
     */
    Integrator(const Input& input, const Function& function);
    
    /**
     * @brief Virtual destructor
     */
    virtual ~Integrator() = default;

    /**
     * @brief Perform the numerical integration
     * @param showSteps Whether to display intermediate steps
     * @return The result of the integration
     */
    virtual double calculate(bool showSteps = true) = 0;
    
    /**
     * @brief Get the name of the integration method
     * @return The method name
     */
    virtual std::string getMethodName() const = 0;
    
    /**
     * @brief Get the result of the integration
     * @return The result (only valid after calculate() is called)
     */
    double getResult() const;
    
    /**
     * @brief Save the results to a file
     * @param filename The name of the file to save to
     * @return True if successful, false otherwise
     */
    bool saveResultToFile(const std::string& filename) const;

protected:
    const Input& input;              // Integration parameters
    const Function& function;        // Function to integrate
    double result;                   // Integration result
    std::vector<double> xValues;     // x values used in integration
    std::vector<double> yValues;     // Corresponding function values
    
    /**
     * @brief Calculate the step size
     * @return The step size
     */
    double calculateStepSize() const;
    
    /**
     * @brief Generate x and y values for integration
     */
    void generatePoints();
    
    /**
     * @brief Display intermediate values during integration
     */
    void displayIntermediateValues() const;
};

} // namespace numerical

#endif // INTEGRATOR_H