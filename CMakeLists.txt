cmake_minimum_required(VERSION 3.10)

project(HelloWorld)

find_package(gRPC CONFIG REQUIRED)

add_library(proto-objects OBJECT "${CMAKE_CURRENT_LIST_DIR}/proto/helloworld/v1/hello_world_api.proto")

target_link_libraries(proto-objects PUBLIC protobuf::libprotobuf gRPC::grpc++)

set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(PROTO_IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}/proto")

target_include_directories(proto-objects PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
    TARGET proto-objects
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

protobuf_generate(
    TARGET proto-objects
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    IMPORT_DIRS ${PROTO_IMPORT_DIRS}
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")


add_executable(HelloWorldServer server.cpp)
target_link_libraries(HelloWorldServer PRIVATE proto-objects)

add_executable(HelloWorldClient client.cpp)
target_link_libraries(HelloWorldClient PRIVATE proto-objects)

