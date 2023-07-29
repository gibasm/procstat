#include "reader.h"
#include "procstat.h"
#include <string.h>
#include <stdio.h>

void* pstat_reader_start(void* arg) {  
    reader_args_t* args = (reader_args_t*)arg;

    char strbuf[args->strbuf_len];

    while(1) {
        read_procstat(strbuf, args->strbuf_len);
        
        while(queue_push(&raw_pstat_fifo, strbuf, strlen((const char*)strbuf)) != QUEUE_SUCCESS);
    }
}
