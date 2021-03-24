add_executable(polymorphism.benchmark polymorphism.benchmark.cpp)
target_link_libraries(polymorphism.benchmark PRIVATE CONAN_PKG::benchmark Threads::Threads)