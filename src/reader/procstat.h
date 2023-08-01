#pragma once

#include <stddef.h>

typedef enum {
    PSTAT_SUCCESS = 0,
    PSTAT_FAILED = 1
} pstat_ret_t;

/**
 * @brief read all of the characters from "/proc/stat" to "outbuf" as a null terminated string
 *
 * @return pstat_ret_t returns FAILED when reading fails, otherwise SUCCESS
 * */
pstat_ret_t read_procstat(char** outbuf);

