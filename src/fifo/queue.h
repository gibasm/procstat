#pragma once

#include <stddef.h>
#include <pthread.h>

typedef enum {
    QUEUE_NONEMPTY = 0,
    QUEUE_EMPTY,
    QUEUE_FULL
} queue_state_t;

typedef struct {
    pthread_mutex_t lock;
    queue_state_t state;
    size_t first_pos, last_pos;
    size_t length, elem_size;
    void** data;
} queue_t;

#define QUEUE_SUCCESS 0

/**
 * @brief initialize and return a queue
 *
 * @param length max number of elements in the queue
 *
 * @param elem_size size of queue element in bytes 
 * 
 * @return queue_t initialized queue object
 */
queue_t queue_init(size_t length, size_t elem_size, void** buffer);

/**
 * @brief push an element pointed to by "elem" to the queue
 * 
 * @param queue queue pointer
 * 
 * @param elem pointer to data to be pushed
 *
 * @return int upon success returns QUEUE_SUCCESS, otherwise QUEUE_FULL
 */
int queue_push(queue_t* queue, void* elem); 

/**
 * @brief pop an element from the queue and copy it to a buffer pointed by "elem"
 *
 * @param queue queue pointer 
 *
 * @param elem pointer to a buffer for the popped element 
 *
 * @return int upon success returns QUEUE_SUCCESS, otherwise QUEUE_EMPTY
 */
int queue_pop(queue_t* queue, void* elem);
