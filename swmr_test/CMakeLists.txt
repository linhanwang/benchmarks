add_executable(atomic_swmr.test atomic_swmr.test.cpp)
target_link_libraries(atomic_swmr.test PRIVATE Threads::Threads)

add_executable(volatile_swmr.test volatile_swmr.test.cpp)
target_link_libraries(volatile_swmr.test PRIVATE Threads::Threads)

add_executable(plain_swmr.test plain_swmr.test.cpp)
target_link_libraries(plain_swmr.test PRIVATE Threads::Threads)