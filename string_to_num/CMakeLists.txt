add_executable(string_to_num.benchmark string_to_num.benchmark.cpp)
target_link_libraries(string_to_num.benchmark PRIVATE CONAN_PKG::benchmark Threads::Threads)