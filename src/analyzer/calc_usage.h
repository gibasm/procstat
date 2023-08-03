#pragma once

#include "parser.h"

typedef struct {
    size_t n_cpus;
    float* usage;
} cpus_usage_t;

/**
 * @brief calculate cpu usage for all cpus
 *
 * @param prev previous time values for all cpus
 * @param next current time values for all cpus
 *
 * @return cpus_usage_t return usage of "n_cpus" in percents [0.0f, 100.0f] in "usage[ncpu]"
 */
cpus_usage_t calc_all_cpus_usage(pstat_cpu_times_t* prev, pstat_cpu_times_t* next);

/**
 * @brief calculate cpu usage for a given cpu
 *
 * @param prev previous time values for a given cpu
 * @param next current time values for a given cpu
 * @param n number of time values in "prev" and "next"
 *
 * @return float percentage [0.0f, 100.0f] of cpu utilization
 */
float calc_cpu_usage(uint64_t* prev, uint64_t* next, size_t n);
