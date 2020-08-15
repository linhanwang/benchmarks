#include <iostream>
#include <thread>
#include <atomic>

#include "utils.h"

using namespace std;

int main() {
    constexpr int loop_time = 10000000;
    atomic<uint64_t> counter{0};

    TimeStampNs start = NowNs();

    thread t1([&counter]() {
        pinThread(1);

        for (int i = 0; i < loop_time; ++i) {
            ++counter;
        }
    });

    thread t2([&counter]() {
        pinThread(2);

        for (int i = 0; i < loop_time; ++i) {
            ++counter;
        }
    });

    thread t3([&counter]() {
        pinThread(3);

        for (int i = 0; i < loop_time; ++i) {
            ++counter;
        }
    });

    t1.join();
    t2.join();
    t3.join();

    TimeStampNs end = NowNs();

    cout << "counter: " << counter << endl;
    cout << "time used: " << end - start << endl;

    return 0;
}
