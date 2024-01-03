cmake_minimum_required(VERSION 3.12)

project(r-type_server)

find_package(
  Boost
  COMPONENTS system
  REQUIRED)

find_package(Protobuf REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp")

add_executable(r-type_server ${SOURCE_FILES})

target_include_directories(r-type_server PRIVATE include)

target_link_libraries(r-type_server PRIVATE Boost::boost Boost::system ${Protobuf_LIBRARIES})

set(PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/network/payload.proto")
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})

target_sources(r-type_server PRIVATE ${PROTO_SRCS} ${PROTO_HDRS})