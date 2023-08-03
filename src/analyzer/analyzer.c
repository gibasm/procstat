#include "analyzer.h"
#include "calc_usage.h"
#include "parser.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

static inline char* copy_queue_first_as_string(queue_t* queue);

void* pstat_analyzer_start(void* arg) {
    sigset_t sigmask;
    sigfillset(&sigmask);
    if(pthread_sigmask(SIG_BLOCK, &sigmask, NULL) != 0)
        return NULL;

    analyzer_args_t* args = (analyzer_args_t*)arg;
    char* next = NULL, * prev = NULL;

    while(!args->done) {

        // get the first reading
        do {
            prev = copy_queue_first_as_string(&raw_pstat_fifo); 
        } while((prev == NULL) && (!args->done));

        while(queue_pop(&raw_pstat_fifo) != QUEUE_SUCCESS) {
            if(args->done)
                break;
        }

        // get the second reading
        do {
            next = copy_queue_first_as_string(&raw_pstat_fifo);
        } while((next == NULL) && (!args->done));

        while(queue_pop(&raw_pstat_fifo) != QUEUE_SUCCESS) {
            if(args->done)
                break;
        }
       
        // parse those strings
        pstat_cpu_times_t prev_parsed, next_parsed;

        if(parse_pstat_string((const char*)prev, &prev_parsed) != PARSER_SUCCESS)
            continue;
        if(parse_pstat_string((const char*)next, &next_parsed) != PARSER_SUCCESS)
            continue;

        free(next);
        next = NULL;

        free(prev);
        prev = NULL;

        // calculate the cpu usage
        cpus_usage_t cpus_usage = calc_all_cpus_usage(&prev_parsed, &next_parsed);
            
        while(queue_push(&printer_fifo, (void*)&cpus_usage.n_cpus, sizeof(size_t)) != QUEUE_SUCCESS) {
                if(args->done)
                    break;
        }

        for(size_t ncpu = 0; ncpu < cpus_usage.n_cpus; ++ncpu) {
            while(queue_push(&printer_fifo, (void*)&cpus_usage.usage[ncpu], sizeof(float)) != QUEUE_SUCCESS) {
                if(args->done)
                    break;
            }
        }

        cpu_times_free(&prev_parsed);
        cpu_times_free(&next_parsed);
    }

    return NULL;
}

static inline char* copy_queue_first_as_string(queue_t* queue) {
    pthread_mutex_lock(&queue->lock);
    
    if(queue->state == QUEUE_EMPTY) {
        pthread_mutex_unlock(&queue->lock);
        return NULL;
    }

    char* first = (char*)queue_get_first(queue);  
    char* str = malloc(strlen(first) + 1U);
    strcpy(str, (const char*)first);        

    pthread_mutex_unlock(&queue->lock);
    
    return str;
}
