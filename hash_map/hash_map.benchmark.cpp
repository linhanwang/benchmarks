#include <absl/container/flat_hash_map.h>
#include <absl/container/node_hash_map.h>
#include <benchmark/benchmark.h>

#include <random>

template <typename MapType>
MapType ConstructRandomMap(int size) {
  std::uniform_int_distribution<int> u(0, size);
  std::default_random_engine e{};

  MapType ret{};
  for (int i = 0; i < size; ++i) {
    ret.insert({u(e), u(e)});
  }
  return ret;
}

static void BM_Baseline(benchmark::State& state) {
  std::uniform_int_distribution<int> u(0, state.range(0));
  std::default_random_engine e{5};
  for (auto _ : state) {
    u(e);
  }
}

static void BM_ToStrBaseline(benchmark::State& state) {
  std::uniform_int_distribution<int> u(1 << 15, 1 << 17);
  std::default_random_engine e{5};
  for (auto _ : state) {
    std::to_string(u(e));
  }
}

template <typename HasherType>
void BM_Hash(benchmark::State& state) {
  HasherType hasher{};
  std::uniform_int_distribution<int> u(1 << 15, 1 << 17);
  std::default_random_engine e{5};
  for (auto _ : state) {
    hasher(std::to_string(u(e)));
  }
}

template <typename T>
void BM_Find(benchmark::State& state) {
  auto data = ConstructRandomMap<T>(state.range(0));
  std::uniform_int_distribution<int> u(0, state.range(0));
  std::default_random_engine e{5};
  for (auto _ : state) {
    data.find(u(e));
  }
}

template <typename T>
void BM_InsertAndDelete(benchmark::State& state) {
  auto data = ConstructRandomMap<T>(state.range(0));
  std::uniform_int_distribution<int> u(0, state.range(0));
  std::default_random_engine e{5};
  for (auto _ : state) {
    auto key = u(e);
    data.insert({key, 0});
    data.erase(key);
  }
}

static void BM_InsertBaseline(benchmark::State& state) {
  for (auto _ : state) {
    state.PauseTiming();
    std::uniform_int_distribution<int> u(0, state.range(0));
    std::default_random_engine e{5};
    state.ResumeTiming();
    for (int j = 0; j < state.range(1); ++j) {
      u(e);
    }
  }
}

template <typename T>
void BM_Insert(benchmark::State& state) {
  T data;
  for (auto _ : state) {
    state.PauseTiming();
    data = ConstructRandomMap<T>(state.range(0));
    std::uniform_int_distribution<int> u(0, state.range(0));
    std::default_random_engine e{5};
    state.ResumeTiming();
    for (int j = 0; j < state.range(1); ++j) data.insert({u(e), 1});
  }
}

template <typename T>
void BM_Iteration(benchmark::State& state) {
  auto data = ConstructRandomMap<T>(state.range(0));
  std::uniform_int_distribution<int> u(0, state.range(0));
  std::default_random_engine e{5};
  for (auto _ : state) {
    int count = 0;
    for (auto& item : data) {
      count += item.second;
    }
  }
}

BENCHMARK(BM_Baseline)->Ranges({{1 << 5, 1 << 12}});
BENCHMARK(BM_ToStrBaseline);

BENCHMARK_TEMPLATE(BM_Hash, std::hash<std::string>);
BENCHMARK_TEMPLATE(BM_Hash, absl::Hash<std::string>);

BENCHMARK_TEMPLATE(BM_Find, std::unordered_map<int, int>)->Ranges({{1 << 5, 1 << 12}});
BENCHMARK_TEMPLATE(BM_Find, absl::flat_hash_map<int, int>)->Ranges({{1 << 5, 1 << 12}});
BENCHMARK_TEMPLATE(BM_Find, absl::node_hash_map<int, int>)->Ranges({{1 << 5, 1 << 12}});


BENCHMARK_TEMPLATE(BM_InsertAndDelete, std::unordered_map<int, int>)->Ranges({{1 << 5, 1 << 12}});
BENCHMARK_TEMPLATE(BM_InsertAndDelete, absl::flat_hash_map<int, int>)->Ranges({{1 << 5, 1 << 12}});
BENCHMARK_TEMPLATE(BM_InsertAndDelete, absl::node_hash_map<int, int>)->Ranges({{1 << 5, 1 << 12}});


BENCHMARK(BM_InsertBaseline)->Ranges({{1 << 10, 8 << 10}, {128, 512}})->Iterations(1000);
BENCHMARK_TEMPLATE(BM_Insert, std::unordered_map<int, int>)->Ranges({{1 << 10, 8 << 10}, {128, 512}})->Iterations(1000);
BENCHMARK_TEMPLATE(BM_Insert, absl::flat_hash_map<int, int>)
    ->Ranges({{1 << 10, 8 << 10}, {128, 512}})
    ->Iterations(1000);
BENCHMARK_TEMPLATE(BM_Insert, absl::node_hash_map<int, int>)
->Ranges({{1 << 10, 8 << 10}, {128, 512}})
    ->Iterations(1000);

BENCHMARK_TEMPLATE(BM_Iteration, std::unordered_map<int, int>)
    ->Ranges({{1 << 10, 8 << 10}, {128, 512}})
    ->Iterations(1000);
BENCHMARK_TEMPLATE(BM_Iteration, absl::flat_hash_map<int, int>)
    ->Ranges({{1 << 10, 8 << 10}, {128, 512}})
    ->Iterations(1000);
BENCHMARK_TEMPLATE(BM_Iteration, absl::node_hash_map<int, int>)
->Ranges({{1 << 10, 8 << 10}, {128, 512}})
    ->Iterations(1000);