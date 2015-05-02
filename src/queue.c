#include "queue.h"

queue_message_t* iterate(queue_t* queue);

queue_t* create(char* name) {
    size_t size = name == NULL ? 0 : strlen(name);
    queue_t* queue = malloc(size + sizeof(queue_t));
    queue->name = name;
    return queue;
}


void destroyQueue(queue_t* queue) {
    free(queue);
}


/*
 * Adds a new element to the queue.
 */
void addElement(queue_t* queue, char* msg) {
    size_t size = msg == NULL? 0 : strlen(msg);
    queue_message_t* queueMessage = malloc(sizeof(queue_message_t) + size);

    queueMessage->msg = msg;

    queue_message_t* previous = iterate(queue);

    if (previous == NULL) {
        queue->first = queueMessage;
    } else {
        previous->next = queueMessage;
    }
}


queue_message_t* iterate(queue_t* queue) {
    queue_message_t* msg = queue->first;
    if (msg == NULL)
        return  NULL;

    while (msg->next != NULL) {
        msg = msg->next;
    }

    return msg;
}

/*
 * Returns the first element in the queue and performs a pointer change. The
 * first element in the queue will be dequeued and the second element becomes
 * the first element in this queue.
 */
queue_message_t* next(queue_t* queue) {
    queue_message_t* firstElement = queue->first;
    queue->first = firstElement->next;
    return firstElement;
}


/*
 * Performs a "dry" next that will return the first element of the queue without
 * dequeueing it.
 */
queue_message_t* dryNext(queue_t* queue) {
    return queue->first;
}
