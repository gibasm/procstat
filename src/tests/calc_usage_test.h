#include <assert.h>
#include "calc_usage.h"

void calc_cpu_usage_should_return_100_percent_for_full_utilization() {
    uint64_t prev[] = { 100, 10, 1, 0, 0, 1 };
    uint64_t next[] = { 110, 20, 1, 0, 0, 1 };
        
    assert(calc_cpu_usage(prev, next, 6UL) == 100.0f);
}

void calc_cpu_usage_should_return_25_percent_for_quarter_utilization() {
    uint64_t prev[] = { 0, 0, 0, 0, 0, 0 };
    uint64_t next[] = { 50, 0, 0, 150, 0, 0 };
   
    assert(calc_cpu_usage(prev, next, 6UL) == 25.0f);
}

