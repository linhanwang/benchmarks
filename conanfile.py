from conans import ConanFile, CMake, tools


class BenchmarksConan(ConanFile):
    name = "benchmarks"
    version = "latest"
    license = "linhan"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": True}
    generators = "cmake"
    requires = "gtest/1.10.0", "glog/0.4.0", "benchmark/1.5.2", "rapidjson/1.1.0", "nlohmann_json/3.9.0", \
               "taskflow/2.5.0", "blaze/3.8"

    scm = {
        "type": "git",
        "url": "git@github.com:linhanwang/benchmarks.git",
        "revision": "master"
    }

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder="./")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include")