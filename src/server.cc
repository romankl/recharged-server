#include "server.h"

namespace recharged {
namespace internal {

Server* Server::sharedServer() {
  if (sharedInstance == nullptr)
    sharedInstance = new Server();
  return sharedInstance;
}

}  // internal
}  // recharged
