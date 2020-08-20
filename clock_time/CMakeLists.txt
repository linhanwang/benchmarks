cmake_minimum_required(VERSION 3.16)
project(time_benchmark)

#set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(time.bench get_time.bench.cpp)
target_link_libraries(time.bench PUBLIC ${CONAN_LIBS})
