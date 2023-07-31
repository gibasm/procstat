#include "fifo/queue.h"
#include "reader/reader.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define READER_FIFO_LEN 16UL

queue_t raw_pstat_fifo;

int main(void) {          
    raw_pstat_fifo = queue_init(READER_FIFO_LEN);

    pthread_t reader_thread;  
    reader_args_t reader_args = {
        .done = false
    };

    if(pthread_create(&reader_thread, NULL, pstat_reader_start, &reader_args) != 0) {
        return 1;
    }

    reader_args.done = true;

    pthread_join(reader_thread, NULL);
   
    queue_free(&raw_pstat_fifo);    

    return 0;
}
