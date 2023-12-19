cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(r-type-revival VERSION 0.1)

add_subdirectory(client)
add_subdirectory(server)
