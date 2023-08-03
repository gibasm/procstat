#include "fifo/queue.h"
#include "reader/reader.h"
#include "analyzer/analyzer.h"
#include "printer/printer.h"
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define READER_FIFO_LEN 16UL
#define PRINTER_FIFO_LEN 16UL

queue_t raw_pstat_fifo;
queue_t printer_fifo;

static pthread_t reader_thread;
static reader_args_t reader_args = {
    .done = false
};

static pthread_t analyzer_thread;
static analyzer_args_t analyzer_args = {
    .done = false
};

static pthread_t printer_thread;
static printer_args_t printer_args = {
    .done = false
};

/**
 * @brief safely exit the program, wait for all the threads to finish and free any dynamic buffers
 */
static void main_exit();

/**
 * @brief safely stop the reader thread
 */
static void stop_reader();

/**
 * @brief safely stop the analyzer thread 
 */
static void stop_analyzer();

/**
 * @brief safely stop the printer thread
 */
static void stop_printer();

int main(void) {          
    raw_pstat_fifo = queue_init(READER_FIFO_LEN);
    printer_fifo = queue_init(PRINTER_FIFO_LEN);

    if(pthread_create(&reader_thread, NULL, pstat_reader_start, &reader_args) != 0) {
        queue_free(&raw_pstat_fifo);
        queue_free(&printer_fifo);
        return EXIT_FAILURE;
    }

    if(pthread_create(&analyzer_thread, NULL, pstat_analyzer_start, &analyzer_args) != 0) {
        stop_reader();

        queue_free(&raw_pstat_fifo);
        queue_free(&printer_fifo);
        return EXIT_FAILURE;
    }
    
    if(pthread_create(&printer_thread, NULL, pstat_printer_start, &printer_args) != 0) {
        stop_analyzer();
        stop_reader();

        queue_free(&printer_fifo);  
        queue_free(&raw_pstat_fifo);
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
    stop_printer();
    stop_analyzer();
    stop_reader();

    queue_free(&printer_fifo);  
    queue_free(&raw_pstat_fifo);
}

static void stop_reader() {
    reader_args.done = true;  
    pthread_join(reader_thread, NULL);
}

static void stop_analyzer() {
    analyzer_args.done = true;
    pthread_join(analyzer_thread, NULL);
}

static void stop_printer() {
    printer_args.done = true;
    pthread_join(printer_thread, NULL);
}
