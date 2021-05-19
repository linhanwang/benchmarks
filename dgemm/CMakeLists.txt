add_executable(dgemm.bench dgemm.bench.cpp)
target_link_libraries(dgemm.bench PRIVATE CONAN_PKG::benchmark)

add_executable(dgemm2.bench dgemm.test.cpp)
target_link_libraries(dgemm2.bench PRIVATE CONAN_PKG::gflags)

add_executable(pi.bench pi.bench.cpp)
target_link_libraries(pi.bench PRIVATE CONAN_PKG::benchmark)