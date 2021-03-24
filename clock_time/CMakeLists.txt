add_executable(time.bench get_time.bench.cpp)
target_link_libraries(time.bench PRIVATE CONAN_PKG::benchmark Threads::Threads)
