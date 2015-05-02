#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <string.h>

typedef struct {
    uint64_t id;
    char* msg;       // content of the message
    void* next;
} queue_message_t;


typedef struct {
    queue_message_t* first; // first element in the queue
    char* name;             // optional human readable name
} queue_t;


queue_t* create(char* name);
void destroyQueue(queue_t* queue);
void addElement(queue_t* queue, char* msg);
queue_message_t* next(queue_t* queue);
queue_message_t* dryNext(queue_t* queue);

#endif
