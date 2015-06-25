#ifndef _SRC_SERVER_H_
#define _SRC_SERVER_H_

#include <stdlib.h>
#include <string>

#include "jsapi.h"
#include "uv.h"

using namespace JS;

namespace recharged {
namespace internal {
  class Server {
  public:
      JSRuntime* jsRuntime; /* JS Spidermonkey runtime */
      JSContext* jsContext;  /* Context for a js runtime */

      uv_tcp_t* tcpLoop;

      unsigned int port;
      int pid;
      unsigned int systemUptime;
      unsigned int uptime;
      uint64_t totalMemory;
  };
}  // internal
}  // recharged

#endif
