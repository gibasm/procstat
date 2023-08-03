#include "printer.h"
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

void* pstat_printer_start(void* arg) {
    sigset_t sigmask;
    sigfillset(&sigmask);
    if(pthread_sigmask(SIG_BLOCK, &sigmask, NULL) != 0)
        return NULL;

    printer_args_t* args = (printer_args_t*) arg;

    float usage = 0.0f;
    size_t n_cpus = 0UL;

    while(!args->done) {
        system("clear");

        while(queue_copy_first_and_pop(&printer_fifo, (void*)&n_cpus, sizeof(size_t)) != QUEUE_SUCCESS) {
                if(args->done)
                    break;
        }

        while(queue_copy_first_and_pop(&printer_fifo, (void*)&usage, sizeof(float)) != QUEUE_SUCCESS) {
                if(args->done)
                    break;
        }
   

        printf("overall\t[%3.1f%%]\n", usage);
        
        for(size_t ncpu = 1; ncpu < n_cpus; ++ncpu) {

            while(queue_copy_first_and_pop(&printer_fifo, (void*)&usage, sizeof(float)) != QUEUE_SUCCESS) {
                if(args->done)
                    break;
            }

            printf("cpu%zu\t[%3.1f%%]\n", ncpu-1UL, usage);
        }

        usleep(PRINTER_DELAY_US);
    }

    return NULL;
}

