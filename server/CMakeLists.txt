cmake_minimum_required(VERSION 3.12)

project(r-type_server)

find_package(
  Boost
  COMPONENTS system
  REQUIRED)

find_package(Protobuf REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/proto/*.cc")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

INCLUDE_DIRECTORIES(${Protobuf_INCLUDE_DIRS})

add_executable(r-type_server ${SOURCE_FILES})

target_link_libraries(r-type_server PRIVATE Boost::boost Boost::system proto)

target_include_directories(r-type_server PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
