#include <benchmark/benchmark.h>

#include <assert.h>

struct Foo {
    uint8_t m1;
    uint64_t m2;
    uint8_t m3;
    uint32_t m4;
    uint16_t m5;
    uint32_t m6;
    uint64_t m7;
};
static_assert(28 < sizeof(Foo));

struct __attribute__((packed)) FooPacked {
    uint8_t m1; // 1
    uint64_t m2; // 8
    uint8_t m3; // 1
    uint32_t m4; // 4
    uint16_t m5; // 2
    uint32_t m6; // 4
    uint64_t m7; // 8
};
static_assert(28 == sizeof(FooPacked));


static void BM_STRUCT_SUM(benchmark::State& state) {
    volatile Foo foo = {1, 2, 3, 4, 5, 6, 7};
    for (auto _ : state) {
        auto haha = foo.m1 + foo.m2 + foo.m3 + foo.m4 + foo.m5 + foo.m6 + foo.m7;
    }
}

static void BM_PACKED_STRUCT_SUM(benchmark::State& state) {
    volatile Foo foo = {1, 2, 3, 4, 5, 6, 7};
    for (auto _ : state) {
        auto haha = foo.m1 + foo.m2 + foo.m3 + foo.m4 + foo.m5 + foo.m6 + foo.m7;
    }
}

// Register the function as a benchmark
BENCHMARK(BM_STRUCT_SUM);
BENCHMARK(BM_PACKED_STRUCT_SUM);

// Run the benchmark
BENCHMARK_MAIN();
