#ifndef _SRC_SERVER_H_
#define _SRC_SERVER_H_

#include <stdlib.h>
#include <string>

#include "uv.h"
#include "mapping.h"
#include "queue.h"


namespace recharged {
namespace internal {

class Server
{
    public:
        static Server& GetInstance() {
            static Server instance;
            return instance;
        }

        typedef int (&commandFunction)(Ast*, uv_buf_t*);

        uv_tcp_t* tcpLoop;

        unsigned int port;
        int pid;
        unsigned int startedTime;
        uint64_t totalMemory;
        Mapping<commandFunction>* cmdMap;
        Mapping<Queue*>* queues;

    private:
        Server() {};

        Server(Server const&);
        void operator=(Server const&);
};

}  // internal
}  // recharged

#endif
