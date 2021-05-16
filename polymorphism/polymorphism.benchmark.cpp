#include <benchmark/benchmark.h>

#include <memory>
#include <functional>

struct Base {
  virtual int& Add() = 0;
};

struct Derived : public Base {
  int data{0};

  int& Add() override { return ++data; }
};

struct Derived1 : public Base {
  int data{0};

  int& Add() override { return data += 2; }
};

struct Derived2 : public Base {
  int data{0};

  int& Add() override { return data += 3; }
};

struct Derived3 : public Base {
  int data{0};

  int& Add() override { return data += 4; }
};

static void BM_DynamicPolymorphism(benchmark::State& state) {
  Derived1 derived1{};
  Derived3 derived3{};
  Base* base{nullptr};

  benchmark::DoNotOptimize(base = &derived3);
  for (auto _ : state) {
    for (int i = 0; i < 1024; ++i) {
      benchmark::DoNotOptimize(base->Add());
    }
  }
}


struct StaticDerived {
  int data{0};

  int& Add() { return ++data; }
};

struct StaticDerived1 {
  int data{0};

  int& Add() { return data += 2; }
};

struct StaticDerived2 {
  int data{0};

  int& Add() { return data += 3; }
};

struct StaticDerived3 {
  int data{0};

  int& Add() { return data += 4; }
};

struct ILogicManager {
  virtual void MainLoop() = 0;
  virtual ~ILogicManager() = default;
};

template <class T>
struct LogicManager : public ILogicManager {
  void MainLoop() final {
    for (int i = 0; i < 1024; ++i) {
      benchmark::DoNotOptimize(adder.Add());
    }
  }

  T adder{};
};

std::unique_ptr<ILogicManager> Factory(int router) {
  switch (router) {
    case 0:
      return std::make_unique<LogicManager<StaticDerived>>();
    case 1:
      return std::make_unique<LogicManager<StaticDerived1>>();
    case 2:
      return std::make_unique<LogicManager<StaticDerived2>>();
    default:
      return std::make_unique<LogicManager<StaticDerived3>>();
  }
}


static void BM_StaticPolymorphism(benchmark::State& state) {
  auto logic = Factory(3);
  for (auto _ : state) {
    logic->MainLoop();
  }
}

static void BM_StaticPolymorphism2(benchmark::State& state) {
  StaticDerived3 derived{};

  for (auto _ : state) {
    for (int i = 0; i < 1024; ++i) {
      benchmark::DoNotOptimize(derived.Add());
    }
  }
}

// Register the function as a benchmark
BENCHMARK(BM_DynamicPolymorphism);
BENCHMARK(BM_StaticPolymorphism);
BENCHMARK(BM_StaticPolymorphism2);

// Run the benchmark