cmake_minimum_required(VERSION 3.12)

project(r-type_server)

find_package(
  Boost
  COMPONENTS system
  REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(r-type_server ${SOURCE_FILES})

target_include_directories(r-type_server PRIVATE include)

target_link_libraries(r-type_server PRIVATE Boost::boost Boost::system)
