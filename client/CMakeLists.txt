cmake_minimum_required(VERSION 3.12)
project(r-type_client)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(Protobuf REQUIRED)

# include_directories(${PROTOBUF_INCLUDE_DIRS})
# include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.cc")

add_executable(r-type_client ${SOURCE_FILES})

target_include_directories(r-type_client PRIVATE include)

target_compile_definitions(r-type_client PRIVATE ASSETS_DIR="${ASSETS_DIR}")

target_link_libraries(
  r-type_client
  PRIVATE
  sfml-system
  sfml-window
  sfml-graphics
  sfml-network
  sfml-audio
  Boost::boost
  Boost::system
  ${Protobuf_LIBRARIES}
)

set(PROTO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/network/payload.proto")
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
target_include_directories(r-type_client PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_sources(r-type_client PRIVATE ${PROTO_SRCS} ${PROTO_HDRS})
