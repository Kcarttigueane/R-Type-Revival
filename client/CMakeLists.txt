# Define the client target
add_executable(r-type_client src/main.cpp)

# Include directories for client
target_include_directories(r-type_client PRIVATE include)

# Link libraries (if any), for example: target_link_libraries(Client
# some_library)
