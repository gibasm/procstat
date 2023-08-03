#include "reader.h"
#include "procstat.h"
#include "config.h"
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void* pstat_reader_start(void* arg) { 
    sigset_t sigmask;
    sigfillset(&sigmask);
    if(pthread_sigmask(SIG_BLOCK, &sigmask, NULL) != 0)
        return NULL;

    char* pstat_rawstr = NULL;
    reader_args_t* args = (reader_args_t*)arg;

    while(!args->done) {
        if(read_procstat(&pstat_rawstr) == PSTAT_FAILED)
            continue;
        
        while(queue_push(&raw_pstat_fifo, (void*)pstat_rawstr, strlen((const char*)pstat_rawstr)) != QUEUE_SUCCESS) {
            if(args->done)
                break;
        }

        free(pstat_rawstr);
        pstat_rawstr = NULL;
        usleep(READER_DELAY_US);
    }

    return NULL;
}
