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
    size_t length;
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
queue_t queue_init(size_t length);

/**
 * @brief push an element pointed to by "elem" to the queue
 * 
 * @param queue queue pointer
 * 
 * @param elem pointer to data to be pushed
 *
 * @return int upon success returns QUEUE_SUCCESS, otherwise QUEUE_FULL
 */
int queue_push(queue_t* queue, void* elem, size_t size); 

/**
 * @brief pop an element from the queue
 *
 * @param queue queue pointer 
 *
 * @return int upon success returns QUEUE_SUCCESS, otherwise QUEUE_EMPTY
 */
int queue_pop(queue_t* queue);

/**
 * @brief read the first element in the queue
 *
 * @param queue queue pointer
 *
 * @return void* a pointer to the first element in the queue
 */
void* queue_get_first(queue_t* queue);

/**
 * @brief free the memory allocated for the queue
 * 
 * @param queu queue pointer
 */
void queue_free(queue_t* queue);

/**
 * @brief copy the "buffer_size" bytes from the first element of the queue to the "buffer", then pop the queue 
 *
 * @param queue queue pointer
 *
 * @param buffer buffer to copy to
 *
 * @param buffer_size size of the buffer to be copied to
 *
 * @return int unon success returns QUEUE_SUCCESS, otherwise QUEUE_EMPTY
 */
int queue_copy_first_and_pop(queue_t* queue, void* buffer, size_t buffer_size);
