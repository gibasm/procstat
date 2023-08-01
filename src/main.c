#include "fifo/queue.h"
#include "reader/reader.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define READER_FIFO_LEN 16UL

queue_t raw_pstat_fifo;

static pthread_t reader_thread;
static reader_args_t reader_args = {
    .done = false
};

/**
 * @brief safely exit the program, wait for all the threads to finish and free any dynamic buffers
 */
static void main_exit();

int main(void) {          
    raw_pstat_fifo = queue_init(READER_FIFO_LEN);

    if(pthread_create(&reader_thread, NULL, pstat_reader_start, &reader_args) != 0) {
        return EXIT_FAILURE;
    }

    int retval = EXIT_SUCCESS;

    sigset_t sigmask;
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGINT); 
    int signum;
    
    if(sigwait(&sigmask, &signum) != 0) {
        retval = EXIT_FAILURE;
    }

    if(pthread_sigmask(SIG_BLOCK, &sigmask, NULL) != 0) {
        retval = EXIT_FAILURE;
    }

    main_exit();

    return retval; 
}

static void main_exit() {
    reader_args.done = true;  
    pthread_join(reader_thread, NULL);
    queue_free(&raw_pstat_fifo);
}
