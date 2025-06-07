#ifndef ROMBERG_H
#define ROMBERG_H

#include "../integrator.h"
#include <vector>

namespace numerical {

/**
 * @class RombergIntegration
 * @brief Implements Romberg integration method
 * 
 * Romberg integration uses extrapolation to improve the accuracy of
 * the trapezoidal rule.
 */
class RombergIntegration : public Integrator {
public:
    /**
     * @brief Constructor
     * @param input Parameters for integration
     * @param function Function to integrate
     * @param order The order of Romberg integration
     */
    RombergIntegration(const Input& input, const Function& function, int order = 4);
    
    /**
     * @brief Perform the integration using Romberg method
     * @param showSteps Whether to display intermediate steps
     * @return The result of the integration
     */
    double calculate(bool showSteps = true) override;
    
    /**
     * @brief Get the name of the method
     * @return The method name
     */
    std::string getMethodName() const override;

private:
    int order;                          // Order of Romberg integration
    std::vector<std::vector<double>> R; // Romberg table
};

} // namespace numerical

#endif // ROMBERG_H