cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(r-type-revival VERSION 0.1)

add_subdirectory(client)
add_subdirectory(server)

enable_testing()

install(TARGETS r-type_client DESTINATION bin)
install(TARGETS r-type_server DESTINATION bin)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${r-type-revival_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${r-type-revival_VERSION_MINOR}")
include(CPack)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --verbose --output-on-failure
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Running tests"
)

file(GLOB TEST_SOURCES "tests/*.cpp")
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} gtest gtest_main)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    add_dependencies(run_tests ${TEST_NAME})
endforeach()
