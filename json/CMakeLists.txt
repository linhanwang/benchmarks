add_executable(json.bench json.benchmark.cpp)
target_link_libraries(json.bench PRIVATE CONAN_PKG::benchmark Threads::Threads CONAN_PKG::nlohmann_json CONAN_PKG::rapidjson)