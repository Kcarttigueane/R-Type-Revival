# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.22)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
# Require the C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name
project(r-type-revival VERSION 0.1)

# Add subdirectories
add_subdirectory(client)
add_subdirectory(server)
