cmake_minimum_required(VERSION 3.10)
project(NumericalIntegration VERSION 2.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define source files
set(SOURCES
    src/main.cpp
    src/function.cpp
    src/input.cpp
    src/integrator.cpp
    src/utils.cpp
    src/methods/trapezoidal.cpp
    src/methods/simpson13.cpp
    src/methods/simpson38.cpp
    src/methods/boole.cpp
    src/methods/romberg.cpp
)

# Define include directories
include_directories(include)

# Create executable
add_executable(NumericalIntegration ${SOURCES})

# Add compiler warnings
if(MSVC)
    target_compile_options(NumericalIntegration PRIVATE /W4 /D_CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(NumericalIntegration PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Install targets
install(TARGETS NumericalIntegration
        RUNTIME DESTINATION bin)

# CPack packaging configuration
set(CPACK_PACKAGE_NAME "NumericalIntegration")
set(CPACK_PACKAGE_VENDOR "Prathamesh Khade")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Numerical Integration Calculator")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_INSTALL_DIRECTORY "NumericalIntegration")

if(WIN32)
    set(CPACK_GENERATOR "NSIS;ZIP")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop;ZIP")
else()
    set(CPACK_GENERATOR "DEB;TGZ")
endif()

include(CPack)