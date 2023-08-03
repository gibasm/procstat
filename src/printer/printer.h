#pragma once

#include "queue.h"

extern queue_t printer_fifo;

typedef struct {
    bool done;
} printer_args_t;

void* pstat_printer_start(void* arg);
