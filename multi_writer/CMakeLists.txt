cmake_minimum_required(VERSION 3.17)
project(mult_writer_test)

set(CMAKE_CXX_STANDARD 14)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(atmomic_test atomic_test.cpp)
target_link_libraries(atmomic_test PRIVATE Threads::Threads)

add_executable(volatile_test volatile_test.cpp)
target_link_libraries(volatile_test PRIVATE Threads::Threads)

add_executable(plain_test plain_test.cpp)
target_link_libraries(plain_test PRIVATE Threads::Threads)