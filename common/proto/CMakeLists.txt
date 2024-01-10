find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIR})

protobuf_generate_cpp(PROTO_SRC PROTO_HEADER payload.proto)

add_library(proto ${PROTO_SRC} ${PROTO_HEADER})
target_include_directories(proto PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${Protobuf_INCLUDE_DIRS})
target_link_libraries(proto PUBLIC ${Protobuf_LIBRARIES})
