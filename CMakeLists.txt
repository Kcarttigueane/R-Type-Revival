cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(r-type-revival VERSION 0.1)

add_subdirectory(client)
add_subdirectory(server)

install(TARGETS r-type_client DESTINATION bin)
install(TARGETS r-type_server DESTINATION bin)


include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${r-type-revival_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${r-type-revival_VERSION_MINOR}")
include(CPack)