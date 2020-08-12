cmake_minimum_required(VERSION 3.16)
project(json_benchmark)

#set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(json_benchmark main.cpp)
target_link_libraries(json_benchmark PUBLIC ${CONAN_LIBS})