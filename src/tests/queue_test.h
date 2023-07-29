#pragma once
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define QUEUE_SIZE 2UL

const char* str = "Test";

void queue_push_should_return_success_when_nonfull() { 
    queue_t queue = queue_init(QUEUE_SIZE);

    assert(queue_push(&queue, (void*)str, strlen(str) + 1) == QUEUE_SUCCESS);
 
    queue_free(&queue);
}

void queue_pop_should_return_success_when_nonempty() { 
    queue_t queue = queue_init(QUEUE_SIZE);

    queue_push(&queue, (void*)str, strlen(str) + 1);
        
    char* first = queue_get_first(&queue);
    assert(strcmp((const char*)str, (const char*)first) == 0);
    assert(queue_pop(&queue) == QUEUE_SUCCESS);

    queue_free(&queue);
}

void queue_push_should_return_queue_full_when_full() {
    queue_t queue = queue_init(QUEUE_SIZE);
   
    for(size_t i = 0; i < QUEUE_SIZE; ++i)
        assert(queue_push(&queue, (void*)str, strlen(str) + 1) == QUEUE_SUCCESS);

    assert(queue.state == QUEUE_FULL); 
    assert(queue_push(&queue, (void*)str, strlen(str) + 1) == QUEUE_FULL);
    
    queue_free(&queue);
}

void queue_pop_should_return_queue_empty_when_empty() {
    queue_t queue = queue_init(QUEUE_SIZE);

    assert(queue_pop(&queue) == QUEUE_EMPTY);    

    queue_free(&queue);
}

