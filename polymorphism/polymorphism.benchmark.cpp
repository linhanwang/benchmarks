#include <benchmark/benchmark.h>

#include <vector>

struct Base {
    virtual void Add() = 0;
};

struct Derived : public Base {
    int data {0};

    void Add() override {
        ++data;
    }
};

struct Derived1 : public Base {
    int data {0};

    void Add() override {
        data+=2;
    }
};

struct Derived2 : public Base {
    int data {0};

    void Add() override {
        data+=3;
    }
};

struct Derived3 : public Base {
    int data {0};

    void Add() override {
        data+=4;
    }
};

void DynamicPolymorphicTranverse(std::vector<Base*>& vec) {
    for (auto& item : vec) {
        item->Add();
    }
}

template <typename T>
void StaticPolymorphicTranverse(std::vector<T*>& vec) {
    for (auto& item : vec) {
        item->Add();
    }
}

static void BM_DynamicPolymorphism(benchmark::State& state) {
    std::vector<Base*> base_vec;

    Derived2 derived;

    for (int i = 0; i < 100; ++i) {
        base_vec.emplace_back(&derived);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(derived.data);
        DynamicPolymorphicTranverse(base_vec);
    }
}

static void BM_StaticPolymorphism(benchmark::State& state) {
    std::vector<Derived2*> vec;

    Derived2 derived;

    for (int i = 0; i < 100; ++i) {
        vec.emplace_back(&derived);
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(derived.data);
        StaticPolymorphicTranverse(vec);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_DynamicPolymorphism);
BENCHMARK(BM_StaticPolymorphism);

// Run the benchmark