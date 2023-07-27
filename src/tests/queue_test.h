#pragma once
#include <assert.h>
#include <stdlib.h>
#include "queue.h"

#define QUEUE_SIZE 2UL

#define QUEUE_ELEM_SIZE 32UL

char** allocate_strbuf(size_t size, size_t n);

void free_strbuf(char** strbuf, size_t n);

void queue_push_should_return_success_when_nonfull() { 
    char** strbuf = allocate_strbuf(QUEUE_ELEM_SIZE, QUEUE_SIZE); 

    char str[QUEUE_ELEM_SIZE] = "Test";

    queue_t queue = queue_init(QUEUE_SIZE, QUEUE_ELEM_SIZE, (void**)strbuf);

    assert(queue_push(&queue, str) == QUEUE_SUCCESS);
 
    free_strbuf(strbuf, QUEUE_SIZE); 
}

void queue_pop_should_return_success_when_nonempty() { 
    char** strbuf = allocate_strbuf(QUEUE_ELEM_SIZE, QUEUE_SIZE); 
    
    char str[QUEUE_ELEM_SIZE] = "Test";

    queue_t queue = queue_init(QUEUE_SIZE, QUEUE_ELEM_SIZE, (void**)strbuf);

    queue_push(&queue, str);
    
    char readbuf[QUEUE_ELEM_SIZE] = "";
    assert(queue_pop(&queue, readbuf) == QUEUE_SUCCESS);
    assert(strcmp((const char*)str, (const char*)readbuf) == 0);
    
    free_strbuf(strbuf, QUEUE_SIZE); 
}

void queue_push_should_return_queue_full_when_full() {
    char** strbuf = allocate_strbuf(QUEUE_ELEM_SIZE, QUEUE_SIZE); 

    char str[QUEUE_ELEM_SIZE] = "Test";

    queue_t queue = queue_init(QUEUE_SIZE, QUEUE_ELEM_SIZE, (void**)strbuf);
    
    for(size_t i = 0; i < QUEUE_SIZE; ++i)
        assert(queue_push(&queue, str) == QUEUE_SUCCESS);

    assert(queue.state == QUEUE_FULL); 
    assert(queue_push(&queue, str) == QUEUE_FULL);
    
    free_strbuf(strbuf, QUEUE_SIZE);
}

void queue_pop_should_return_queue_empty_when_empty() {
    char* strbuf[QUEUE_SIZE];
    for(size_t i = 0; i < QUEUE_SIZE; ++i) 
        strbuf[i] = malloc(QUEUE_ELEM_SIZE);
    
    queue_t queue = queue_init(QUEUE_SIZE, QUEUE_ELEM_SIZE, (void**)strbuf);

    char readbuf[QUEUE_ELEM_SIZE] = "";
    assert(queue_pop(&queue, readbuf) == QUEUE_EMPTY);
    
    for(size_t i = 0; i < QUEUE_SIZE; ++i) 
        free(strbuf[i]);
}

char** allocate_strbuf(size_t size, size_t n) {
    char** strbuf = calloc(n, sizeof(char*));
    for(size_t i = 0; i < n; ++i) 
        strbuf[i] = malloc(size);
    return strbuf;
}

void free_strbuf(char** strbuf, size_t n) {
    for(size_t i = 0; i < n; ++i)
        free(strbuf[i]);
    free(strbuf);
}

