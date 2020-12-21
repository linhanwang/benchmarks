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

/*
 * Generate 64-bit timestamp.
 */
static __inline__ long long NowTscNs(void) {
    unsigned int __a,__d;

    __asm__ __volatile__("rdtsc" : "=a" (__a), "=d" (__d));
    return ((long long)__a) | (((long long)__d)<<32);
}

inline void pinThread(int cpu) {
    if (cpu < 0) {
        return;
    }

#ifndef __APPLE__
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(cpu, &cpuset);
    if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset) != 0) {
        perror("pthread_setaffinity_np");
        exit(1);
    }
#endif
}