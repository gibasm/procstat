#include "fifo/queue.h"
#include "reader/reader.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define READER_FIFO_LEN 16UL

queue_t raw_pstat_fifo;

int main(void) {          
    raw_pstat_fifo = queue_init(READER_FIFO_LEN);

    reader_args_t reader_args = {
        .strbuf_len = 256UL
    };

    pthread_t reader_thread;  
    if(pthread_create(&reader_thread, NULL, pstat_reader_start, (void*)&reader_args) != 0) {
        return 1;
    }

    pthread_cancel(reader_thread);
   
    queue_free(&raw_pstat_fifo);    

    return 0;
}
