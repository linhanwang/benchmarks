#include <atomic>
#include <iostream>
#include <thread>
#include <vector>

#include "utils.h"

using namespace std;

int main() {
  constexpr int N = 2;
  vector<TimeStampNs> record_times(N + 1, 0);
  vector<thread> threads;

  int signal{0};

  threads.emplace_back([&]() {
    pinThread(3);

    struct timespec sleep_timespec;
    sleep_timespec.tv_nsec = 1;
    sleep_timespec.tv_sec = 1;

    nanosleep(&sleep_timespec, nullptr);

    signal = 100230;
    record_times[0] = NowNs();
  });

  for (int i = 1; i <= N; ++i) {
    threads.emplace_back([&signal, &record_times, i]() {
      pinThread(i);

      while (signal != 100230) {
      }
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
