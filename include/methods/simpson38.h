#ifndef SIMPSON38_H
#define SIMPSON38_H

#include "../integrator.h"

namespace numerical {

/**
 * @class SimpsonThreeEighth
 * @brief Implements Simpson's 3/8 rule for numerical integration
 * 
 * Simpson's 3/8 rule approximates the definite integral by using cubic
 * interpolation between function values.
 */
class SimpsonThreeEighth : public Integrator {
public:
    /**
     * @brief Constructor
     * @param input Parameters for integration
     * @param function Function to integrate
     */
    SimpsonThreeEighth(const Input& input, const Function& function);
    
    /**
     * @brief Perform the integration using Simpson's 3/8 rule
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

#endif // SIMPSON38_H