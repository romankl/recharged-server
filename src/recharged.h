#ifndef __RECHARGED_H__
#define __RECHARGED_H__

#include "uv.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    char* command;
    char* value;
} recharged_command_t;


typedef struct {
  uv_write_t request;
  uv_buf_t buf;
  recharged_command_t command;
} incoming_write_req_t;


typedef struct {
    void* next;
    void* previous;
    void* content;
} list_object_t;


typedef struct {
    list_object_t* first;
    list_object_t* last;

    long count;
} list_head_t;


struct server_t {
    uint64_t startedTime;
    uint64_t totalMemory;
    int protocol;
    list_head_t* queues; // all queues that are currently allocated
};


// Message structure
typedef struct {
    uint64_t id;
    char* msg;       // content of the message
    void* next;
} queue_message_t;


// General queue structure
typedef struct {
    queue_message_t* first; // first element in the queue
    queue_message_t* last;
    char* name;             // optional human readable name
} queue_t;


struct server_t sharedServer;


queue_t* createQueue(incoming_write_req_t *incoming, char* name);
void destroyQueue(incoming_write_req_t *incoming, queue_t* queue);
void addElement(incoming_write_req_t *incoming, queue_t* queue, char* msg);
queue_message_t* next(incoming_write_req_t *incoming, queue_t* queue);
queue_message_t* dryNext(incoming_write_req_t *incoming, queue_t* queue);
void flushQueue(queue_t* queue);

list_head_t* createList();
void addListElement(list_head_t* list, list_object_t* element);

#endif
