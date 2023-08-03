#pragma once

#include <inttypes.h>
#include <stddef.h>

typedef struct {
    size_t n_cpus; 
    size_t n_times;
    uint64_t** cpu_times;  
} pstat_cpu_times_t;

typedef enum {
    PARSER_SUCCESS,
    PARSER_FAILED
} parser_ret_t;


/**
 * @brief parse string "pstat_str" read from /proc/stat and extract time values for each cpu to "pstat_cpu_times"
 *
 * @param pstat_str string containing the characters read from /proc/stat
 *
 * @param pstat_cpu_times pointer to a structure that'll contain the extracted values
 *
 * @return upon success returns "PARSER_SUCCESS", otherwise "PARSER_FAILED"
 */
parser_ret_t parse_pstat_string(const char* pstat_str, pstat_cpu_times_t* pstat_cpu_times);

/**
 * @brief free the "cpu_times" buffer in "pstat_cpu_times"
 */
void cpu_times_free(pstat_cpu_times_t* pstat_cpu_times);
