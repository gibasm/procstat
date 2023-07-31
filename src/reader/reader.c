#include "reader.h"
#include "procstat.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void* pstat_reader_start(void* arg) { 
    char* pstat_rawstr = NULL;
    reader_args_t* args = (reader_args_t*)arg;

    while(!args->done) {
        read_procstat(&pstat_rawstr);
        
        while(queue_push(&raw_pstat_fifo, (void*)pstat_rawstr, strlen((const char*)pstat_rawstr)) != QUEUE_SUCCESS);

        free(pstat_rawstr);
        pstat_rawstr = NULL;
    }

    return NULL;
}
