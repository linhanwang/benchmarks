add_executable(simd_sum.benchmark simd_sum.benchmark.cpp)
target_link_libraries(simd_sum.benchmark PUBLIC ${CONAN_LIBS})