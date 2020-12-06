add_executable(atmomic_multi_writer.test atomic_multi_writer.test.cpp ../simd_sum/simd_sum.benchmark.cpp ../polymorphism/polymorphism.benchmark.cpp)
target_link_libraries(atmomic_multi_writer.test PRIVATE Threads::Threads)

add_executable(volatile_multi_writer.test volatile_multi_writer.test.cpp)
target_link_libraries(volatile_multi_writer.test PRIVATE Threads::Threads)

add_executable(plain_multi_writer.test plain_multi_writer.test.cpp)
target_link_libraries(plain_multi_writer.test PRIVATE Threads::Threads)