#include <taskflow/taskflow.hpp>
#include <benchmark/benchmark.h>

#include <utils.h>

void loop() {
    auto start = NowNs();
    while (NowNs() < start + 500);
}

void loop3() {
    auto start = NowNs();
    while (NowNs() < start + 1500);
}

static void BM_TASKFLOW(benchmark::State& state) {
    tf::Executor executor;
    tf::Taskflow taskflow("simple");

    auto A = taskflow.emplace([]() { loop(); });
    auto B = taskflow.emplace([]() { loop(); });
    auto C = taskflow.emplace([]() { loop(); });
    auto D = taskflow.emplace([]() { loop(); });

    A.precede(B);
    A.precede(C);
    B.precede(D);
    C.precede(D);
    for (auto _ : state) {
        executor.run(taskflow).wait();
    }
}

static void BM_SEQUENTIAL(benchmark::State& state) {
    for (auto _ : state) {
        loop3();
    }
}

// Register the function as a benchmark
BENCHMARK(BM_TASKFLOW);
BENCHMARK(BM_SEQUENTIAL);

