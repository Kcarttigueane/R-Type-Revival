cmake_minimum_required(VERSION 3.12)
project(r-type_client)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)

# Set the directory containing your assets
set(ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")

# Define the client target
add_executable(r-type_client src/main.cpp)

# Include directories for client
target_include_directories(r-type_client PRIVATE include)

# Define a compile definition for the assets directory
target_compile_definitions(r-type_client PRIVATE ASSETS_DIR="${ASSETS_DIR}")

# Link SFML and Boost to your target
target_link_libraries(
  r-type_client
  PRIVATE sfml-system
          sfml-window
          sfml-graphics
          sfml-network
          sfml-audio
          Boost::boost
          Boost::system)
