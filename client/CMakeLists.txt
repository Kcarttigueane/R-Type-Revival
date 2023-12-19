# Include directories for client target_include_directories(r-type_client
# PRIVATE include)

find_package(
  SFML
  COMPONENTS system window graphics CONFIG
  REQUIRED)

find_package(
  Boost
  COMPONENTS system
  REQUIRED)

# Get all source files in the src/ directory
file(GLOB SOURCE_FILES "src/*.cpp")

# Define the client target
add_executable(r-type_client ${SOURCE_FILES})

# Link SFML to your target
target_link_libraries(
  r-type_client
  PRIVATE sfml-system
          sfml-window
          sfml-graphics
          sfml-network
          sfml-audio
          Boost::boost
          Boost::system)
