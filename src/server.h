#ifndef _SRC_SERVER_H_
#define _SRC_SERVER_H_

#include <stdlib.h>
#include <string>

namespace recharged {
namespace internal {
  class Server {
    public:
      static Server* sharedServer();

      private:
        Server() {};

        static Server* sharedInstance;
  };
}  // internal
}  // recharged

#endif
