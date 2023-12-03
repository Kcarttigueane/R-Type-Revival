# Define the server target
add_executable(r-type_server src/main.cpp)

# Include directories for server
target_include_directories(r-type_server PRIVATE include)

# Link libraries for the server target_link_libraries(Server some_other_library)
