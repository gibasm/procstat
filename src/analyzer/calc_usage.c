#include "calc_usage.h"
#include <stdlib.h>

#define TIME_IDLE_POS 3
#define TIME_IOWAIT_POS 4

cpus_usage_t calc_all_cpus_usage(pstat_cpu_times_t* prev, pstat_cpu_times_t* next) {
    cpus_usage_t cpus_usage = {
        .n_cpus = prev->n_cpus,
        .usage = calloc(prev->n_times, sizeof(unsigned char*))
    };

    for(size_t ncpu = 0; ncpu < cpus_usage.n_cpus; ++ncpu) {
        cpus_usage.usage[ncpu] = calc_cpu_usage(prev->cpu_times[ncpu], next->cpu_times[ncpu], prev->n_times);
    }

    return cpus_usage;
}

float calc_cpu_usage(uint64_t* prev, uint64_t* next, size_t n) {
    uint64_t prev_idle = prev[TIME_IDLE_POS] + prev[TIME_IOWAIT_POS];
    uint64_t next_idle = next[TIME_IDLE_POS] + next[TIME_IOWAIT_POS];

    uint64_t prev_total = 0, next_total = 0;

    for(size_t time_pos = 0; time_pos < n; ++time_pos) { 
        prev_total += prev[time_pos];
        next_total += next[time_pos];
    }

    uint64_t total_diff = next_total - prev_total;
    uint64_t idle_diff = next_idle - prev_idle; 

    if(total_diff == 0UL)
        return 0.0f;

    return ((total_diff - idle_diff) / (total_diff * 1.0f)) * 100.0f;
}
