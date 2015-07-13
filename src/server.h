#ifndef _SRC_SERVER_H_
#define _SRC_SERVER_H_

#include <stdlib.h>
#include <string>
#include <functional>
#include <unordered_map>


#include "uv.h"
#include "mapping.h"
#include "ast.h"


namespace recharged {
namespace internal {

// Forward declaration to avoid circles.
class Queue;

class Server
{
    public:
        static Server& GetInstance() {
            static Server instance;
            return instance;
        }

        uv_tcp_t* tcpLoop;

        unsigned int port;
        int pid;
        unsigned int startedTime;
        uint64_t totalMemory;
        Mapping<std::function<std::string(Ast*, uv_buf_t*)> >* cmdMap;
        Mapping<Queue*>* queues;

    private:
        Server() {};

        Server(Server const&);
        void operator=(Server const&);
};

}  // internal
}  // recharged

#endif
