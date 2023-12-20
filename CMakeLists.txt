# Set the minimum version of CMake that can be used
cmake_minimum_required(VERSION 3.27)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
# Require the C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name
project(r-type-revival VERSION 0.1)

# Add subdirectories
add_subdirectory(client)
add_subdirectory(server)

# Add the 'make test' rule
enable_testing()

# Add the 'run_tests' target (changed from 'test' to avoid conflict)
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests"
)

# Add a test for each test suite in the test folder
file(GLOB TEST_SOURCES "tests/*.cpp")
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} gtest gtest_main)  # Link against Google Test libraries
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    add_dependencies(run_tests ${TEST_NAME})
endforeach()
