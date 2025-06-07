#ifndef BOOLE_H
#define BOOLE_H

#include "../integrator.h"

namespace numerical {

/**
 * @class BooleRule
 * @brief Implements Boole's rule for numerical integration
 * 
 * Boole's rule approximates the definite integral by using a fourth-degree
 * polynomial interpolation between function values.
 */
class BooleRule : public Integrator {
public:
    /**
     * @brief Constructor
     * @param input Parameters for integration
     * @param function Function to integrate
     */
    BooleRule(const Input& input, const Function& function);
    
    /**
     * @brief Perform the integration using Boole's rule
     * @param showSteps Whether to display intermediate steps
     * @return The result of the integration
     */
    double calculate(bool showSteps = true) override;
    
    /**
     * @brief Get the name of the method
     * @return The method name
     */
    std::string getMethodName() const override;
    
    /**
     * @brief Check if the method is applicable for the given number of intervals
     * @return True if applicable, false otherwise
     */
    bool isApplicable() const;
};

} // namespace numerical

#endif // BOOLE_H