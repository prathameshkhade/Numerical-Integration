#ifndef TRAPEZOIDAL_H
#define TRAPEZOIDAL_H

#include "../integrator.h"

namespace numerical {

/**
 * @class TrapezoidalRule
 * @brief Implements the Trapezoidal rule for numerical integration
 * 
 * The Trapezoidal rule approximates the definite integral by using linear
 * interpolation between function values.
 */
class TrapezoidalRule : public Integrator {
public:
    /**
     * @brief Constructor
     * @param input Parameters for integration
     * @param function Function to integrate
     */
    TrapezoidalRule(const Input& input, const Function& function);
    
    /**
     * @brief Perform the integration using the Trapezoidal rule
     * @param showSteps Whether to display intermediate steps
     * @return The result of the integration
     */
    double calculate(bool showSteps = true) override;
    
    /**
     * @brief Get the name of the method
     * @return The method name
     */
    std::string getMethodName() const override;
};

} // namespace numerical

#endif // TRAPEZOIDAL_H