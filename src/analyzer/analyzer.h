#pragma once 
#include "queue.h"

extern queue_t raw_pstat_fifo;
extern queue_t printer_fifo;

typedef struct {
    bool done;
} analyzer_args_t;

void* pstat_analyzer_start(void* arg); 
