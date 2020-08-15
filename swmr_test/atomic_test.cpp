#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

#include "utils.h"

using namespace std;

int main() {
    constexpr int N = 2;
    vector<TimeStampNs> record_times(N + 1, 0);
    vector<thread> threads;

    atomic<uint64_t> signal{0};

    threads.emplace_back([&] () {
        pinThread(3);

        struct timespec sleep_timespec;
        sleep_timespec.tv_nsec = 1;
        sleep_timespec.tv_sec = 1;

        nanosleep(&sleep_timespec, nullptr);

        signal.store(100230, memory_order_relaxed);
        record_times[0] = NowNs();
    });

    for (int i = 1; i <= N; ++i) {
        threads.emplace_back([&signal, &record_times, i]() {
            pinThread(i);

            while (signal.load(memory_order_relaxed) != 100230) {}
            record_times[i] = NowNs();
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    for (int i = 0; i <= N; ++i) {
        cout << record_times[i] - record_times[0] << " ";
    }

    cout << endl;

    return 0;
}
