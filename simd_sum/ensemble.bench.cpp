#include <benchmark/benchmark.h>
#include <blaze/Blaze.h>

#include <cstring>
#include <random>

#define VCL_NAMESPACE vcl
#include <vectorclass.h>

template <std::size_t N>
class RandomTerms {
 public:
  RandomTerms() {
    std::uniform_int_distribution<int> u(0, 1);
    std::default_random_engine e{};

    for (int i = 0; i < 64; ++i) {
      blaze::StaticVector<double, N> terms{};
      for (int i = 0; i < N; ++i) {
        terms[i] = u(e);
      }

      terms_vec.push_back(terms);
    }
  }

  const blaze::StaticVector<double, N>& GetTerms() {
    return terms_vec[counter++ & 63];
  }

 private:
  std::vector<blaze::StaticVector<double, N>> terms_vec{};
  unsigned int counter{};
};

template <std::size_t N>
class Terms {
 public:
  Terms() {
    std::uniform_int_distribution<int> u(0, 1);
    std::default_random_engine e{};

    for (int i = 0; i < N; ++i) {
      maxes[i] = u(e);
      mins[i] = u(e);
      weights[i] = u(e);
    }
  }

  double GetYhat(const blaze::StaticVector<double, N>& input) {
    std::memcpy(terms.data() + N, terms.data(), N * sizeof(double));
    std::memcpy(terms.data(), input.data(), N * sizeof(double));
    blaze::subvector(terms, 2 * N, N) = input - blaze::subvector(terms, N, N);

    terms = blaze::min(terms, maxes);
    terms = blaze::max(terms, mins);
    return blaze::dot(terms, weights);
  }

 private:
  blaze::StaticVector<double, 3 * N> terms{};
  blaze::StaticVector<double, 3 * N> mins{};
  blaze::StaticVector<double, 3 * N> maxes{};
  blaze::StaticVector<double, 3 * N> weights{};
};

template <std::size_t N>
class TermsOptimized {
 public:
  TermsOptimized() {
    std::uniform_int_distribution<int> u(0, 1);
    std::default_random_engine e{};

    for (int i = 0; i < N; ++i) {
      maxes[i] = u(e);
      mins[i] = u(e);
      weights[i] = u(e);
    }
  }

  double GetYhat(const blaze::StaticVector<double, N>& input) {
    blaze::StaticVector<double, N> temp{};

    temp = blaze::max(input, blaze::subvector<blaze::aligned>(mins, 0, N));
    temp = blaze::min(temp, blaze::subvector<blaze::aligned>(maxes, 0, N));
    double yhat = blaze::dot(temp, blaze::subvector<blaze::aligned>(weights, 0, N));

    yhat += blaze::dot(terms, blaze::subvector(weights, N, N));

    temp = input - terms;
    temp = blaze::max(temp, blaze::subvector<blaze::aligned>(mins, 0, N));
    temp = blaze::min(temp, blaze::subvector<blaze::aligned>(maxes, 0, N));
    yhat += blaze::dot(temp, blaze::subvector(weights, 2 * N, N));

    std::memcpy(terms.data(), input.data(), N * sizeof(double));

    return yhat;
  }

 private:
  blaze::StaticVector<double, N> terms{};
  blaze::StaticVector<double, 3 * N> mins{};
  blaze::StaticVector<double, 3 * N> maxes{};
  blaze::StaticVector<double, 3 * N> weights{};
};

template <std::size_t N>
class TermsOptimized2 {
 public:
  TermsOptimized2() {
    std::uniform_int_distribution<int> u(0, 1);
    std::default_random_engine e{};

    for (int i = 0; i < 8; ++i) {
      maxes[i] = u(e);
      mins[i] = u(e);
      weights[i] = u(e);
    }
    idx = {10, 11, 37, 38, 54, 55, 77, 78};
  }

  double GetYhat(const blaze::StaticVector<double, N>& input) {
    std::memcpy(terms.data() + N, terms.data(), N * sizeof(double));
    std::memcpy(terms.data(), input.data(), N * sizeof(double));
    blaze::subvector(terms, 2 * N, N) = input - blaze::subvector(terms, N, N);

    blaze::StaticVector<double, 8> temp{};
    for (int i = 0; i < 8; ++i) {
      temp[i] = terms[idx[i]];
    }

    temp = blaze::max(temp, mins);
    temp = blaze::min(temp, maxes);
    return blaze::dot(temp, weights);
  }

 private:
  blaze::StaticVector<double, 3 * N> terms{};
  blaze::StaticVector<double, 8> mins{};
  blaze::StaticVector<double, 8> maxes{};
  blaze::StaticVector<double, 8> weights{};

  std::vector<int> idx{};
};

template <std::size_t N>
static void BM_baseline(benchmark::State& state) {
  RandomTerms<N> terms_generator{};
  Terms<N> terms{};

  for (auto _ : state) {
    benchmark::DoNotOptimize(terms.GetYhat(terms_generator.GetTerms()));
    benchmark::DoNotOptimize(terms);
  }
}

BENCHMARK_TEMPLATE(BM_baseline, 35);

template <std::size_t N>
static void BM_Optimized(benchmark::State& state) {
  RandomTerms<N> terms_generator{};
  TermsOptimized<N> terms{};

  for (auto _ : state) {
    benchmark::DoNotOptimize(terms.GetYhat(terms_generator.GetTerms()));
    benchmark::DoNotOptimize(terms);
  }
}

BENCHMARK_TEMPLATE(BM_Optimized, 35);

template <std::size_t N>
static void BM_Optimized2(benchmark::State& state) {
  RandomTerms<N> terms_generator{};
  TermsOptimized2<N> terms{};

  for (auto _ : state) {
    benchmark::DoNotOptimize(terms.GetYhat(terms_generator.GetTerms()));
    benchmark::DoNotOptimize(terms);
  }
}

BENCHMARK_TEMPLATE(BM_Optimized2, 35);