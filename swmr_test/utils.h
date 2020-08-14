#pragma once

#include <stdint.h>
#include <time.h>
#include <pthread.h>

using TimeStampNs = int64_t;
using TimePeriodNs = int64_t;

inline TimeStampNs NowNs() {
    static struct timespec curr_timespec;
    clock_gettime(CLOCK_REALTIME, &curr_timespec);

    return curr_timespec.tv_sec * 1000000000ll + curr_timespec.tv_nsec;
}

inline void pinThread(int cpu) {
    if (cpu < 0) {
        return;
    }
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, &cpuset);
    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0) {
        perror("pthread_setaffinity_np");
        exit(1);
    }
}