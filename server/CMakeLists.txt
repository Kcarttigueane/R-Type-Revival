find_package(
  Boost
  COMPONENTS system
  REQUIRED)

add_executable(r-type_server src/main.cpp)

target_link_libraries(r-type_server PRIVATE Boost::boost Boost::system)
