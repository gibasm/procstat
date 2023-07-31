#pragma once
#include "queue.h"

extern queue_t raw_pstat_fifo;

typedef struct {
    bool done;
} reader_args_t;

/**
 * @brief /proc/stat reader start routine, pushes a string read from /proc/stat to "raw_pstat_fifo"
 */
void* pstat_reader_start(void* arg);
