cmake_minimum_required(VERSION 3.12)
project(r-type_client)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

file(GLOB SOURCE_FILES "src/*.cpp")

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
)
