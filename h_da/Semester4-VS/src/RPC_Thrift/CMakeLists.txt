cmake_minimum_required(VERSION 3.19)
project(RPC_Thrift)
link_libraries(thrift)
set(CMAKE_CXX_STANDARD 14)
SET(GCC_COVERAGE_COMPILE_FLAGS "-lthrift")
set(GCC_COVERAGE_LINK_FLAGS "-lthrift")
add_executable(RPC_Thrift_Server server-main.cpp gen-cpp/example_constants.h gen-cpp/example_constants.cpp gen-cpp/Example.h gen-cpp/Example.cpp gen-cpp/example_types.h gen-cpp/example_types.cpp)
add_executable(RPC_Thrift_Client client-main.cpp)

