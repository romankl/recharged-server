#ifndef __RECHARGED_H__
#define __RECHARGED_H__

#include "uv.h"
#include "error.h"
#include "queue.h"

struct server_t {
    uint64_t startedTime;
    uint64_t totalMemory;
    int protocol;
};

#endif
