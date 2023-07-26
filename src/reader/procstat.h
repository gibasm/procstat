#pragma once

#include <stddef.h>

typedef enum {
    SUCCESS = 0,
    FAILED = 1
} pstat_ret_t;

/**
 * @brief read maximum of "size" characters from "/proc/stat" to "outbuf" as a null terminated string
 *
 * @return pstat_ret_t returns FAILED when reading fails, otherwise SUCCESS
 * */
pstat_ret_t read_procstat(char* outbuf, size_t size);

