#pragma once
#include "queue.h"

extern queue_t raw_pstat_fifo;

typedef struct {
    size_t strbuf_len; /* reader string buffer's length */
} reader_args_t;

/**
 *  @brief /proc/stat reader start routine 
 *  
 *  @param args pointer to reader_args_t
 */
void* pstat_reader_start(void* arg);
