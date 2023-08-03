#include "queue.h"
#include <memory.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#define NEXTPOS(pos, size) ((pos + 1) % size)

#define LAST(queue) (queue->data[queue->last_pos])

#define FIRST(queue) (queue->data[queue->first_pos])

queue_t queue_init(size_t length) {
    queue_t queue = {
        .state = QUEUE_EMPTY,
        .last_pos = 0,
        .first_pos = 0,
        .length = length,
    };
 
    queue.data = (void**)calloc(length, sizeof(void*));

    for(size_t i = 0; i < queue.length; ++i) {
        queue.data[i] = NULL;
    }

    pthread_mutex_init(&queue.lock, NULL);

    return queue; 
}


int queue_push(queue_t* queue, void* elem, size_t size) {
    pthread_mutex_lock(&queue->lock);

    if(queue->state == QUEUE_FULL) {
        pthread_mutex_unlock(&queue->lock);
        return QUEUE_FULL;
    } 
    
    if(LAST(queue) != NULL) {
        free(LAST(queue));
    }

    LAST(queue) = malloc(size);

    memcpy(LAST(queue), elem, size); 
    queue->last_pos = NEXTPOS(queue->last_pos, queue->length);

    queue->state = queue->first_pos == queue->last_pos ? QUEUE_FULL : QUEUE_NONEMPTY;

    pthread_mutex_unlock(&queue->lock);

    return QUEUE_SUCCESS;
}


int queue_pop(queue_t* queue) {
    pthread_mutex_lock(&queue->lock);

    if(queue->state == QUEUE_EMPTY) {
        pthread_mutex_unlock(&queue->lock);
        return QUEUE_EMPTY;
    }

    queue->first_pos = NEXTPOS(queue->first_pos, queue->length);

    queue->state = queue->first_pos == queue->last_pos ? QUEUE_EMPTY : QUEUE_NONEMPTY;

    pthread_mutex_unlock(&queue->lock);

    return QUEUE_SUCCESS;
}

void* queue_get_first(queue_t* queue) {
    return FIRST(queue); 
}

void queue_free(queue_t* queue) {
    for(size_t i = 0; i < queue->length; ++i) {
        if(queue->data[i] != NULL)
            free(queue->data[i]);
    }
    free(queue->data);

    pthread_mutex_destroy(&queue->lock);
}

int queue_copy_first_and_pop(queue_t* queue, void* buffer, size_t buffer_size) {
    pthread_mutex_lock(&queue->lock);

    if(queue->state == QUEUE_EMPTY) {
        pthread_mutex_unlock(&queue->lock);
        return QUEUE_EMPTY;
    }

    memcpy(buffer, (const void*)FIRST(queue), buffer_size);

    queue->first_pos = NEXTPOS(queue->first_pos, queue->length);

    queue->state = queue->first_pos == queue->last_pos ? QUEUE_EMPTY : QUEUE_NONEMPTY;

    pthread_mutex_unlock(&queue->lock);

    return QUEUE_SUCCESS;
}

