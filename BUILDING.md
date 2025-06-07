# Build Instructions for Numerical Integration Calculator

This document provides detailed instructions for building the Numerical Integration Calculator on different platforms and creating executable packages for distribution.

## Table of Contents

- [Prerequisites](#prerequisites)
- [Build Checklist](#build-checklist)
- [Windows Build](#windows-build)
- [macOS Build](#macos-build)
- [Linux Build](#linux-build)
- [Creating Release Packages](#creating-release-packages)
- [Continuous Integration](#continuous-integration)
- [Troubleshooting](#troubleshooting)

## Prerequisites

Before building the Numerical Integration Calculator, ensure you have the following installed:

- **C++ Compiler**:
  - Windows: Visual Studio 2019 or newer, or MinGW-w64
  - macOS: Xcode Command Line Tools (clang)
  - Linux: GCC 7+ or Clang 5+

- **Build Tools**:
  - CMake 3.10 or newer
  - Git (optional, for version control)
  - Ninja (optional, for faster builds)

- **Dependencies**: All dependencies are standard C++ libraries included with most compilers.

## Build Checklist

Use this checklist to ensure your build environment is properly set up:

- [ ] C++17 compatible compiler is installed and available in PATH
- [ ] CMake 3.10+ is installed and available in PATH
- [ ] Git is installed (if cloning from repository)
- [ ] Build directory is created and separate from source
- [ ] Project compiles without warnings
- [ ] Executable runs correctly
- [ ] Tests pass (if applicable)
- [ ] Documentation is up-to-date

## Windows Build

### Using Visual Studio

1. **Install Visual Studio 2019 or newer**:
   - Make sure to include "Desktop development with C++" workload
   - Include "C++ CMake tools for Windows" component

2. **Open Project**:
   - Launch Visual Studio
   - Select "Open a local folder" and navigate to the project directory
   - Visual Studio will detect CMakeLists.txt and configure the project

3. **Build the Project**:
   - Select a configuration (Debug/Release) in the dropdown
   - Build → Build All
   - Or use keyboard shortcut Ctrl+Shift+B

4. **Run the Application**:
   - Debug → Start Without Debugging (Ctrl+F5)
   - The executable will be in `out/build/<config>/bin/NumericalIntegration.exe`

### Using Command Line (PowerShell/CMD)

1. **Create Build Directory**:
   ```powershell
   mkdir build
   cd build
   ```

2. **Configure with CMake**:
   ```powershell
   cmake -G "Visual Studio 16 2019" -A x64 ..
   ```

3. **Build the Project**:
   ```powershell
   cmake --build . --config Release
   ```

4. **Run the Application**:
   ```powershell
   .\bin\Release\NumericalIntegration.exe
   ```

### Using MinGW

1. **Configure with CMake**:
   ```cmd
   mkdir build
   cd build
   cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
   ```

2. **Build the Project**:
   ```cmd
   cmake --build .
   ```

3. **Run the Application**:
   ```cmd
   .\bin\NumericalIntegration.exe
   ```

## macOS Build

### Using Terminal

1. **Install Build Tools**:
   ```bash
   xcode-select --install
   brew install cmake
   ```

2. **Create Build Directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake**:
   ```bash
   cmake -DCMAKE_BUILD_TYPE=Release ..
   ```

4. **Build the Project**:
   ```bash
   make -j$(sysctl -n hw.ncpu)
   ```

5. **Run the Application**:
   ```bash
   ./bin/NumericalIntegration
   ```

### Using Xcode

1. **Generate Xcode Project**:
   ```bash
   mkdir xcode-build
   cd xcode-build
   cmake -G Xcode ..
   ```

2. **Open in Xcode**:
   ```bash
   open NumericalIntegration.xcodeproj
   ```

3. **Build and Run in Xcode**:
   - Select the "NumericalIntegration" target
   - Select the desired build configuration
   - Click the "Build and Run" button

## Linux Build

### Using Terminal

1. **Install Build Tools**:
   For Debian/Ubuntu:
   ```bash
   sudo apt update
   sudo apt install g++ cmake make git
   ```
   
   For Fedora/RHEL:
   ```bash
   sudo dnf install gcc-c++ cmake make git
   ```

2. **Create Build Directory**:
   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake**:
   ```bash
   cmake -DCMAKE_BUILD_TYPE=Release ..
   ```

4. **Build the Project**:
   ```bash
   make -j$(nproc)
   ```

5. **Run the Application**:
   ```bash
   ./bin/NumericalIntegration
   ```

### Using Ninja (for faster builds)

1. **Install Ninja**:
   ```bash
   sudo apt install ninja-build   # Debian/Ubuntu
   sudo dnf install ninja-build   # Fedora/RHEL
   ```

2. **Configure with CMake using Ninja**:
   ```bash
   mkdir ninja-build
   cd ninja-build
   cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
   ```

3. **Build the Project**:
   ```bash
   ninja
   ```

4. **Run the Application**:
   ```bash
   ./bin/NumericalIntegration
   ```

## Creating Release Packages

The project includes CPack configuration for creating installable packages.

### Windows Installer (NSIS)

1. **Build the project first**:
   ```powershell
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

2. **Create the installer**:
   ```powershell
   cpack -G NSIS
   ```

3. **Create ZIP archive**:
   ```powershell
   cpack -G ZIP
   ```

### macOS Package

1. **Build the project first**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Create DMG**:
   ```bash
   cpack -G DragNDrop
   ```

3. **Create ZIP archive**:
   ```bash
   cpack -G ZIP
   ```

### Linux Package

1. **Build the project first**:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```

2. **Create DEB package (Debian/Ubuntu)**:
   ```bash
   cpack -G DEB
   ```

3. **Create tarball**:
   ```bash
   cpack -G TGZ
   ```

## Continuous Integration

The project includes GitHub Actions workflows for automated building and testing.

### GitHub Actions Workflow

The CI workflow automatically:
- Builds the project on Windows, macOS, and Linux
- Runs tests (if available)
- Creates release packages for each platform
- Attaches packages to GitHub releases when a tag is pushed

## Troubleshooting

### Common Issues

1. **CMake not found**:
   - Ensure CMake is installed and in your PATH
   - Try running `cmake --version` to verify

2. **Compiler not found**:
   - Make sure your compiler is installed correctly
   - Check that it's available in your PATH

3. **Build fails with compiler errors**:
   - Check that you have a C++17 compatible compiler
   - Make sure all source files are properly included in CMakeLists.txt

4. **Program crashes on startup**:
   - Build in Debug mode for more detailed error messages
   - Check for platform-specific code that might not be compatible

5. **Package creation fails**:
   - Ensure you have the required packaging tools installed
   - For NSIS on Windows, make sure NSIS is installed
   - For DEB on Linux, make sure the dpkg tools are installed

For more assistance, please open an issue on the GitHub repository.