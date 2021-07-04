add_executable(arch.bench arch.bench.cpp)
target_link_libraries(arch.bench PRIVATE CONAN_PKG::benchmark Threads::Threads CONAN_PKG::blaze CONAN_PKG::sleef)