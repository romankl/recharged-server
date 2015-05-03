#ifndef __RECHARGED_H__
#define __RECHARGED_H__

#include "uv.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
  uv_write_t request;
  uv_buf_t buf;
} incoming_write_req_t;


struct server_t {
    uint64_t startedTime;
    uint64_t totalMemory;
    int protocol;
};


typedef struct {
    uint64_t id;
    char* msg;       // content of the message
    void* next;
} queue_message_t;


typedef struct {
    queue_message_t* first; // first element in the queue
    queue_message_t* last;
    char* name;             // optional human readable name
} queue_t;


queue_t* create(incoming_write_req_t *incoming, char* name);
void destroyQueue(incoming_write_req_t *incoming, queue_t* queue);
void addElement(incoming_write_req_t *incoming, queue_t* queue, char* msg);
queue_message_t* next(incoming_write_req_t *incoming, queue_t* queue);
queue_message_t* dryNext(incoming_write_req_t *incoming, queue_t* queue);
void flushQueue(queue_t* queue);

#endif
