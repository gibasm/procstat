#pragma once

#include <stddef.h>

typedef enum {
    SUCCESS = 0,
    FAILED = 1
} pstat_ret_t;

/**
 * @brief read maximum of "size" characters from "/proc/stat" to "outbuf" and set "size" to the number of read characters
 *
 * @return pstat_ret_t returns FAILED when reading fails, otherwise SUCCESS
 * */
pstat_ret_t read_procstat(char* outbuf, size_t* size);

