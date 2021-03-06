#include <benchmark/benchmark.h>
#include <stdint.h>
#include <stdio.h>

#include <nlohmann/json.hpp>
#include <unordered_map>

#include "rapidjson/writer.h"  // for stringify JSON

using namespace rapidjson;

struct Pod {
  uint32_t field1;
  char field2[11];
  double field3;
  uint64_t field4;
  double field5;
  uint64_t field6;
  uint64_t field7;
  uint64_t field8;
  uint64_t field9;
  uint64_t field10;

  void SERIALIZE(Writer<StringBuffer>& writer) const {
    writer.StartObject();

    writer.String("field1");
    writer.Uint(field1);

    writer.String("field2");
    writer.String(field2);

    writer.String("field3");
    writer.Double(field3);

    writer.String("field4");
    writer.Uint64(field4);

    writer.String("field5");
    writer.Double(field5);

    writer.String("field6");
    writer.Uint64(field6);

    writer.String("field6");
    writer.Uint64(field6);

    writer.String("field7");
    writer.Uint64(field7);

    writer.String("field8");
    writer.Uint64(field8);

    writer.String("field9");
    writer.Uint64(field9);

    writer.String("field10");
    writer.Uint64(field10);

    writer.EndObject();
  }

  void SERIALIZE() {
    nlohmann::json json = {
        {"field1", field1}, {"field2", field2}, {"field3", field3}, {"field4", field4}, {"field5", field5},
        {"field6", field6}, {"field7", field7}, {"field8", field8}, {"field9", field9}, {"field10", field10},
    };

    json.dump();
  }

  void Snsprintf() {
    char buffer[1024];

    int cx = snprintf(buffer, 1024,
                      "{\"field1\":%d,\"field2\":%s,\"field3\":%lf,\"field4\":%zd,"
                      "\"field5\":%lf,\"field6\":%zd,\"field7\":%zd,\"field8\":%zd,\"field9\":%zd,"
                      "\"field10\":%zd,}",
                      field1, field2, field3, field4, field5, field6, field7, field8, field9, field10);
  }
};

static void BM_RAPIDJSON_SERIALIZE(benchmark::State& state) {
  Pod pod{
      .field1 = 34123,
      .field2 = "wanglinhan",
      .field3 = 1243.121,
      .field4 = 23433,
      .field5 = 234.234,
      .field6 = 23424,
      .field7 = 23424,
      .field8 = 23424,
      .field9 = 23424,
      .field10 = 23424,
  };

  StringBuffer sb;
  Writer<StringBuffer> writer(sb);

  for (auto _ : state) {
    pod.SERIALIZE(writer);
    sb.GetString();
  }
}

static void BM_NLOHMANNJSON_SERIALIZE(benchmark::State& state) {
  Pod pod{
      .field1 = 34123,
      .field2 = "wanglinhan",
      .field3 = 1243.121,
      .field4 = 23433,
      .field5 = 234.234,
      .field6 = 23424,
      .field7 = 23424,
      .field8 = 23424,
      .field9 = 23424,
      .field10 = 23424,
  };

  for (auto _ : state) {
    pod.SERIALIZE();
  }
}

static void BM_SNSPRINTF(benchmark::State& state) {
  Pod pod{
      .field1 = 34123,
      .field2 = "wanglinhan",
      .field3 = 1243.121,
      .field4 = 23433,
      .field5 = 234.234,
      .field6 = 23424,
      .field7 = 23424,
      .field8 = 23424,
      .field9 = 23424,
      .field10 = 23424,
  };

  for (auto _ : state) {
    pod.Snsprintf();
  }
}

// Register the function as a benchmark
BENCHMARK(BM_RAPIDJSON_SERIALIZE);
BENCHMARK(BM_NLOHMANNJSON_SERIALIZE);
BENCHMARK(BM_SNSPRINTF);
