#include "../include/utils.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <ctime>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <unistd.h>
#include <termios.h>
#endif

namespace numerical {
namespace utils {

int getMenuChoice(const std::string& title, const std::vector<std::string>& options, int minOption, int maxOption) {
    if (maxOption < 0) {
        maxOption = static_cast<int>(options.size());
    }
    
    std::cout << "\n" << title << "\n";
    std::cout << std::string(title.length(), '=') << "\n";
    
    for (size_t i = 0; i < options.size(); ++i) {
        std::cout << (i + 1) << ". " << options[i] << "\n";
    }
    
    int choice;
    do {
        std::cout << "\nEnter your choice (" << minOption << "-" << maxOption << "): ";
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            choice = -1;
        }
    } while (choice < minOption || choice > maxOption);
    
    return choice;
}

void waitForKeyPress() {
#ifdef _WIN32
    std::cout << "\nPress any key to continue...";
    _getch();
#else
    std::cout << "\nPress Enter to continue...";
    
    // Temporarily change terminal settings to read a single character
    struct termios oldSettings, newSettings;
    tcgetattr(STDIN_FILENO, &oldSettings);
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
    
    getchar();
    
    // Restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);
#endif
    std::cout << std::endl;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void sleep(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::string formatNumber(double value, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << value;
    return oss.str();
}

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::string getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto now_time_t = std::chrono::system_clock::to_time_t(now);
    
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

} // namespace utils
} // namespace numerical