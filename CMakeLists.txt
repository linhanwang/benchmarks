cmake_minimum_required(VERSION 3.10)
project(benchmarks)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

add_compile_options("-march=broadwell")

add_subdirectory(clock_time)
add_subdirectory(json)
add_subdirectory(multi_writer)
add_subdirectory(swmr_test)
add_subdirectory(packing)
add_subdirectory(taskflow)
add_subdirectory(simd_sum)
add_subdirectory(polymorphism)