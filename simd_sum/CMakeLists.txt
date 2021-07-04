add_executable(simd_sum.benchmark simd_sum.benchmark.cpp)
target_link_libraries(simd_sum.benchmark PRIVATE CONAN_PKG::benchmark Threads::Threads CONAN_PKG::blaze)

add_executable(simd_log.benchmark simd_log.benchmark.cpp)
target_link_libraries(simd_log.benchmark PRIVATE CONAN_PKG::sleef CONAN_PKG::benchmark Threads::Threads CONAN_PKG::blaze)

add_executable(ensemble.bench ensemble.bench.cpp)
target_link_libraries(ensemble.bench PRIVATE CONAN_PKG::sleef CONAN_PKG::benchmark Threads::Threads CONAN_PKG::blaze CONAN_PKG::vectorclass)