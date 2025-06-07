# Numerical Integration Calculator

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Version](https://img.shields.io/badge/version-2.0-green.svg)
![C++](https://img.shields.io/badge/C%2B%2B-17-orange.svg)

A comprehensive C++ application for numerical integration with multiple methods, detailed step-by-step calculations, and comparison capabilities.

## 📝 Table of Contents

- [Numerical Integration Calculator](#numerical-integration-calculator)
  - [📝 Table of Contents](#-table-of-contents)
  - [✨ Features](#-features)
  - [📊 Supported Integration Methods](#-supported-integration-methods)
  - [🚀 Installation](#-installation)
    - [Prerequisites](#prerequisites)
    - [Building from Source](#building-from-source)
    - [Pre-built Binaries](#pre-built-binaries)
  - [📖 Usage](#-usage)
    - [Basic Operation](#basic-operation)
    - [Choosing an Integration Method](#choosing-an-integration-method)
    - [Comparing Methods](#comparing-methods)
    - [Saving and Loading Results](#saving-and-loading-results)
  - [📐 Mathematical Background](#-mathematical-background)
  - [📂 Project Structure](#-project-structure)
  - [🛠️ Build Instructions](#️-build-instructions)
    - [Windows](#windows)
      - [Using Visual Studio](#using-visual-studio)
      - [Using Command Line](#using-command-line)
    - [macOS](#macos)
    - [Linux](#linux)
  - [💡 Contributing](#-contributing)
  - [📜 Changelog](#-changelog)
    - [v2.0.0 (2025-06-07)](#v200-2025-06-07)
    - [v1.0.0 (Initial Release)](#v100-initial-release)
  - [📄 License](#-license)
  - [👨‍💻 Author](#-author)

## ✨ Features

- **Multiple Integration Methods**: Includes Trapezoidal Rule, Simpson's Rules, Boole's Rule, and Romberg Integration
- **Step-by-Step Calculation Display**: See how each method works with detailed intermediate steps
- **Method Comparison**: Compare the accuracy and results of different integration methods
- **Multiple Functions**: Choose from a variety of predefined mathematical functions
- **Result Storage**: Save integration results to files and load them later
- **Cross-Platform**: Works on Windows, macOS, and Linux
- **User-Friendly Interface**: Clear console-based interface with easy navigation

## 📊 Supported Integration Methods

1. **Trapezoidal Rule**: Uses linear approximation between points
   - Formula: `h/2 * [f(a) + f(b) + 2 * sum(f(x_i))]`

2. **Simpson's 1/3 Rule**: Uses quadratic approximation
   - Formula: `h/3 * [f(a) + f(b) + 4 * sum(f(x_odd)) + 2 * sum(f(x_even))]`
   - Requires an even number of intervals

3. **Simpson's 3/8 Rule**: Uses cubic approximation
   - Formula: `3h/8 * [f(a) + f(b) + 3 * sum(f(not divisible by 3)) + 2 * sum(f(divisible by 3))]`
   - Requires a number of intervals divisible by 3

4. **Boole's Rule**: Uses fourth-degree polynomial approximation
   - Formula: `4h/90 * [7(f(a) + f(b)) + 32(f(x1) + f(x3) + ...) + 12(f(x2) + f(x6) + ...) + 14(f(x4) + f(x8) + ...)]`
   - Requires a number of intervals divisible by 4

5. **Romberg Integration**: Uses Richardson extrapolation to improve accuracy
   - Highly accurate for smooth functions
   - Adjustable order for precision control

## 🚀 Installation

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 19.14+)
- CMake 3.10 or higher (for building from source)
- Git (optional, for cloning the repository)

### Building from Source

1. Clone the repository:
   ```bash
   git clone https://github.com/prathameshkhade/Numerical-Integration.git
   cd Numerical-Integration
   ```

2. Create a build directory and navigate to it:
   ```bash
   mkdir build
   cd build
   ```

3. Configure with CMake and build:
   ```bash
   cmake ..
   cmake --build .
   ```

4. Run the executable:
   - Windows: `.\Debug\NumericalIntegration.exe` or `.\Release\NumericalIntegration.exe`
   - macOS/Linux: `./NumericalIntegration`

### Pre-built Binaries

Pre-built binaries for Windows, macOS, and Linux are available in the [Releases](https://github.com/prathameshkhade/Numerical-Integration/releases) section.

## 📖 Usage

### Basic Operation

1. Start the application
2. Select "Perform Integration" from the main menu
3. Choose a function to integrate
4. Enter the lower and upper bounds of integration
5. Specify the number of intervals
6. Select an integration method
7. View the result and step-by-step calculation

### Choosing an Integration Method

- **Trapezoidal Rule**: Good general-purpose method, works with any number of intervals
- **Simpson's 1/3 Rule**: Better accuracy than Trapezoidal for most functions, requires even number of intervals
- **Simpson's 3/8 Rule**: Similar accuracy to 1/3 rule, requires intervals divisible by 3
- **Boole's Rule**: Higher accuracy for smooth functions, requires intervals divisible by 4
- **Romberg Integration**: Highest accuracy, especially for smooth functions

### Comparing Methods

1. Select "Compare All Integration Methods" from the main menu
2. Enter integration parameters (function, bounds, intervals)
3. The program will calculate the integral using all available methods
4. Results are displayed in a comparison table with error estimates

### Saving and Loading Results

- After performing an integration, you can save the result to a file
- Use "Load Previous Results" to view previously saved results
- Result files include all parameters and intermediate values

## 📐 Mathematical Background

Numerical integration methods approximate definite integrals using various techniques:

- **Trapezoidal Rule**: Approximates the area under the curve using trapezoids
- **Simpson's Rules**: Use quadratic (1/3) or cubic (3/8) polynomials to approximate the function
- **Boole's Rule**: Uses fourth-degree polynomials for higher accuracy
- **Romberg Integration**: Applies Richardson extrapolation to the trapezoidal rule

For a function f(x) and an interval [a, b], the definite integral is approximated by dividing the interval into n subintervals and applying the specific formula for each method.

## 📂 Project Structure

```
numerical-integration/
├── include/                # Header files
│   ├── function.h          # Mathematical function definitions
│   ├── input.h             # Input handling class
│   ├── integrator.h        # Base integrator class
│   ├── methods/            # Integration methods
│   │   ├── trapezoidal.h
│   │   ├── simpson13.h
│   │   ├── simpson38.h
│   │   ├── boole.h
│   │   └── romberg.h
│   └── utils.h             # Utility functions
├── src/                    # Implementation files
│   ├── function.cpp
│   ├── input.cpp
│   ├── integrator.cpp
│   ├── methods/
│   │   ├── trapezoidal.cpp
│   │   ├── simpson13.cpp
│   │   ├── simpson38.cpp
│   │   ├── boole.cpp
│   │   └── romberg.cpp
│   ├── utils.cpp
│   └── main.cpp            # Program entry point
├── CMakeLists.txt          # CMake build configuration
├── LICENSE                 # License file
└── README.md               # This file
```

## 🛠️ Build Instructions

### Windows

#### Using Visual Studio

1. Open Visual Studio
2. Select "Open a local folder" and navigate to the repository
3. Visual Studio should detect the CMakeLists.txt and configure the project
4. Build using Build > Build All
5. Run the executable from the output directory

#### Using Command Line

1. Open Command Prompt or PowerShell
2. Navigate to the project directory
3. Create and navigate to a build directory:
   ```cmd
   mkdir build
   cd build
   ```
4. Configure and build with CMake:
   ```cmd
   cmake ..
   cmake --build . --config Release
   ```
5. Run the executable:
   ```cmd
   .\Release\NumericalIntegration.exe
   ```

### macOS

1. Open Terminal
2. Navigate to the project directory
3. Create and navigate to a build directory:
   ```bash
   mkdir build
   cd build
   ```
4. Configure and build with CMake:
   ```bash
   cmake ..
   make
   ```
5. Run the executable:
   ```bash
   ./NumericalIntegration
   ```

### Linux

1. Open a terminal
2. Navigate to the project directory
3. Create and navigate to a build directory:
   ```bash
   mkdir build
   cd build
   ```
4. Configure and build with CMake:
   ```bash
   cmake ..
   make
   ```
5. Run the executable:
   ```bash
   ./NumericalIntegration
   ```

## 💡 Contributing

Contributions are welcome! Here's how you can contribute:

1. Fork the repository
2. Create a new branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Commit your changes (`git commit -m 'Add some amazing feature'`)
5. Push to the branch (`git push origin feature/amazing-feature`)
6. Open a Pull Request

Please ensure your code follows the project's coding style and includes appropriate tests.

## 📜 Changelog

### v2.0.0 (2025-06-07)

- Complete rewrite with modular C++ design
- Added new integration methods (Boole's Rule, Romberg Integration)
- Improved error handling and robustness
- Added method comparison functionality
- Added support for saving/loading results
- Cross-platform compatibility improvements
- Comprehensive documentation

### v1.0.0 (Initial Release)

- Basic implementation with Trapezoidal, Simpson's 1/3, and Simpson's 3/8 rules
- Console-based interface
- Step-by-step calculation display

## 📄 License

This project is licensed under the MIT License - see the LICENSE file for details.

## 👨‍💻 Author

- **Prathamesh Khade** - [GitHub](https://github.com/prathameshkhade)

---

If you find this project useful, please consider giving it a star on GitHub!