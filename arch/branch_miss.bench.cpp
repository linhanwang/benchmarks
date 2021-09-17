#include <benchmark/benchmark.h>
#include <array>


static void BM_condition(benchmark::State& state) {
  std::array<bool, 8> inputs{false, true, false, false, true, false, true, true};

  std::uint32_t counter{};
  for (auto _ : state) {
    auto haha = inputs[counter++ & 7] ? 1.5f : 2.6f;
    benchmark::DoNotOptimize(haha);
  }
}

BENCHMARK(BM_condition);

static void BM_lookup(benchmark::State& state) {
  std::array<bool, 8> inputs{false, true, false, false, true, false, true, true};
  std::array<float, 2> lookup{1.5f, 2.6f};

  std::uint32_t counter{};
  for (auto _ : state) {
    auto haha = lookup[inputs[counter++ & 7]];
    benchmark::DoNotOptimize(haha);
  }
}

BENCHMARK(BM_lookup);

struct Struct1 {
  static constexpr int kKey = 123;
  std::array<char, 8> name{};
  float a1{};
  double b2{};
};

struct Struct2 {
  static constexpr int kKey = 432;
  std::array<char, 8> name{};
  float a1{};
  double b2{};
  std::uint64_t c3{};
};

struct Struct3 {
  static constexpr int kKey = 23465;
  std::array<char, 8> name{};
  float a1{};
  double b2{};
  std::uint64_t c3{};
};

struct Struct4 {
  static constexpr int kKey = 23;
  std::array<char, 8> name{};
  float a1{};
  double b2{};
  std::uint64_t c3{};
};

struct Struct5 {
  static constexpr int kKey = 763;
  std::array<char, 8> name{};
  float a1{};
  double b2{};
  std::uint64_t c3{};
};

struct Struct6 {
  static constexpr int kKey = 81;
  std::array<char, 8> name{};
  float a1{};
  double b2{};
  std::uint64_t c3{};
};

struct Msg {
  int key{};
  char* data{};
  std::size_t len{};
};

struct MdSrc {
  int key{};
  std::array<char, 8> name{};
};

inline MdSrc ExtractMdSrc(const Msg& msg) {
  MdSrc rst{};
  rst.key = msg.key;

  switch(msg.key) {
    case Struct1::kKey:
      rst.name = reinterpret_cast<Struct1*>(msg.data)->name;
      break;
    case Struct2::kKey:
      rst.name = reinterpret_cast<Struct2*>(msg.data)->name;
      break;
    case Struct3::kKey:
      rst.name = reinterpret_cast<Struct3*>(msg.data)->name;
      break;
    case Struct4::kKey:
      rst.name = reinterpret_cast<Struct4*>(msg.data)->name;
      break;
    case Struct5::kKey:
      rst.name = reinterpret_cast<Struct5*>(msg.data)->name;
      break;
    case Struct6::kKey:
      rst.name = reinterpret_cast<Struct6*>(msg.data)->name;
      break;
    default:
      rst.name = std::array<char, 8>{"234"};
  }

  return rst;
}

static void BM_condition2(benchmark::State& state) {
  std::array<Msg, 4> msgs{};
  Struct1 data1{"hehe", 3.3, 23.2};
  Struct4 data2{"heahe", 3.3, 23.2, 45};
  Struct2 data3{"here", 3.3, 23.2};
  Struct5 data4{"hehe", 3.3, 23.2, 76};

  msgs[0] = Msg{Struct1::kKey, reinterpret_cast<char*>(&data1), sizeof(Struct1)};
  msgs[1] = Msg{Struct4::kKey, reinterpret_cast<char*>(&data2), sizeof(Struct4)};
  msgs[2] = Msg{Struct2::kKey, reinterpret_cast<char*>(&data3), sizeof(Struct2)};
  msgs[3] = Msg{Struct5::kKey, reinterpret_cast<char*>(&data4), sizeof(Struct5)};

  std::uint32_t counter{};
  for (auto _ : state) {
    auto haha = ExtractMdSrc(msgs[counter++ & 3]);
    benchmark::DoNotOptimize(haha);
  }
}

BENCHMARK(BM_condition2);

inline MdSrc ExtractDirect(const Msg& msg) {
  MdSrc md_src{};
  md_src.key = msg.key;
  md_src.name = reinterpret_cast<Struct1*>(msg.data)->name;
  return md_src;
}

static void BM_direct(benchmark::State& state) {
  std::array<Msg, 4> msgs{};
  Struct1 data1{"hehe", 3.3, 23.2};
  Struct4 data2{"heahe", 3.3, 23.2, 45};
  Struct2 data3{"here", 3.3, 23.2};
  Struct5 data4{"hehe", 3.3, 23.2, 76};

  msgs[0] = Msg{Struct1::kKey, reinterpret_cast<char*>(&data1), sizeof(Struct1)};
  msgs[1] = Msg{Struct4::kKey, reinterpret_cast<char*>(&data2), sizeof(Struct4)};
  msgs[2] = Msg{Struct2::kKey, reinterpret_cast<char*>(&data3), sizeof(Struct2)};
  msgs[3] = Msg{Struct5::kKey, reinterpret_cast<char*>(&data4), sizeof(Struct5)};

  std::uint32_t counter{};
  for (auto _ : state) {
    auto haha = ExtractDirect(msgs[counter++ & 3]);
    benchmark::DoNotOptimize(haha);
  }
}

BENCHMARK(BM_direct);

