# Minimum required version of CMake
cmake_minimum_required(VERSION 3.15)

# Project name and language
project(Matrix VERSION 1.0 LANGUAGES CXX)

# Require C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # Disable compiler-specific extensions
cmake_policy(SET CMP0135 NEW)

# Compiler flags for strict warnings and better code quality
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# ==========================================
# Dependency Search
# ==========================================

# Find ncurses (CMake has a built-in module for this)
find_package(Curses REQUIRED)

# ==========================================
# Executable Configuration
# ==========================================

# Collect all source files
set(SOURCES
    main.cpp
)

# Create the executable
add_executable(plusmatrix ${SOURCES})

# ==========================================
# Linking and Include Directories
# ==========================================

# Tell the compiler where your project's .hpp files are located
target_include_directories(plusmatrix PRIVATE include)

# Include dependency headers
target_include_directories(plusmatrix PRIVATE 
    ${CURSES_INCLUDE_DIRS}
)

# Link libraries to the executable
target_link_libraries(plusmatrix PRIVATE 
    ${CURSES_LIBRARIES}
)

# ==========================================
# Installation Block
# ==========================================

# GNUInstallDirs defines standard installation directories in Linux
include(GNUInstallDirs)

# Installation block to place the binary in the correct system or local path
install(TARGETS plusmatrix
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)