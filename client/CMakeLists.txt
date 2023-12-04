# Include directories for client
# target_include_directories(r-type_client PRIVATE include)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# Define the client target
add_executable(r-type_client src/main.cpp)

# Link SFML to your target
target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics)
