#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace numerical {

/**
 * @namespace utils
 * @brief Utility functions for the numerical integration library
 */
namespace utils {

/**
 * @brief Display a menu and get user choice
 * @param title The menu title
 * @param options The menu options
 * @param minOption The minimum allowed option number
 * @param maxOption The maximum allowed option number
 * @return The chosen option
 */
int getMenuChoice(const std::string& title, const std::vector<std::string>& options, 
                  int minOption = 1, int maxOption = -1);

/**
 * @brief Wait for user to press a key
 */
void waitForKeyPress();

/**
 * @brief Clear the console screen
 */
void clearScreen();

/**
 * @brief Wait for specified milliseconds
 * @param ms The number of milliseconds to wait
 */
void sleep(int ms);

/**
 * @brief Format a number with specified precision
 * @param value The value to format
 * @param precision The number of decimal places
 * @return The formatted string
 */
std::string formatNumber(double value, int precision = 6);

/**
 * @brief Check if a file exists
 * @param filename The name of the file to check
 * @return True if the file exists, false otherwise
 */
bool fileExists(const std::string& filename);

/**
 * @brief Generate a timestamp string
 * @return The current timestamp as a string
 */
std::string getTimestamp();

} // namespace utils

} // namespace numerical

#endif // UTILS_H