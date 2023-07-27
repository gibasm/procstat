#include "queue.h"
#include <memory.h>
#include <pthread.h>
#include <stdio.h>

#define NEXTPOS(pos, size) ((pos + 1) % size)

#define LAST(queue) (queue->data[queue->last_pos])

#define FIRST(queue) (queue->data[queue->first_pos])


queue_t queue_init(size_t length, size_t elem_size, void** buffer) {
    queue_t queue = {
        .state = QUEUE_EMPTY,
        .last_pos = 0,
        .first_pos = 0,
        .length = length,
        .elem_size = elem_size,
        .data = buffer
    };

    pthread_mutex_init(&queue.lock, NULL);

    return queue; 
}


int queue_push(queue_t* queue, void* elem) {
    pthread_mutex_lock(&queue->lock);

    if(queue->state == QUEUE_FULL) {
        pthread_mutex_unlock(&queue->lock);
        return QUEUE_FULL;
    }

    memcpy(LAST(queue), elem, queue->elem_size); 
    queue->last_pos = NEXTPOS(queue->last_pos, queue->length);

    queue->state = queue->first_pos == queue->last_pos ? QUEUE_FULL : QUEUE_NONEMPTY;

    pthread_mutex_unlock(&queue->lock);

    return QUEUE_SUCCESS;
}


int queue_pop(queue_t* queue, void* elem) {
    pthread_mutex_lock(&queue->lock);

    if(queue->state == QUEUE_EMPTY) {
        pthread_mutex_unlock(&queue->lock);
        return QUEUE_EMPTY;
    }

    memcpy(elem, FIRST(queue), queue->elem_size);
    queue->first_pos = NEXTPOS(queue->first_pos, queue->length);

    queue->state = queue->first_pos == queue->last_pos ? QUEUE_EMPTY : QUEUE_NONEMPTY;

    pthread_mutex_unlock(&queue->lock);

    return QUEUE_SUCCESS;
}

