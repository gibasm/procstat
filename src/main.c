#include "fifo/queue.h"
#include "reader/reader.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define READER_STRBUF_LEN 256UL
#define READER_FIFO_LEN 16UL

queue_t raw_pstat_fifo;
char* raw_pstat_buffer[READER_FIFO_LEN];

void alloc_buffers();

void free_buffers();

int main(void) {      
    alloc_buffers();
    
    raw_pstat_fifo = queue_init(READER_FIFO_LEN, READER_STRBUF_LEN, (void**)raw_pstat_buffer);

    reader_args_t reader_args = {
        .strbuf_len = READER_STRBUF_LEN
    };

    pthread_t reader_thread;  
    if(pthread_create(&reader_thread, NULL, pstat_reader_start, (void*)&reader_args) != 0) {
        return 1;
    }

    pthread_cancel(reader_thread);
    
    free_buffers();
    
    pthread_mutex_destroy(&raw_pstat_fifo.lock);

    return 0;
}

void alloc_buffers() {
    for(size_t i = 0; i < READER_FIFO_LEN; ++i)
        raw_pstat_buffer[i] = calloc(READER_STRBUF_LEN, sizeof(char));
}

void free_buffers() {
    for(size_t i = 0; i < READER_FIFO_LEN; ++i)
        free(raw_pstat_buffer[i]);
}
