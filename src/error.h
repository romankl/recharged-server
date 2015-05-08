#ifndef _SRC_ERROR_H_
#define _SRC_ERROR_H_

#include <stdlib.h>
#include <string>

namespace recharged {
namespace internal {

  class Error {
  public:
    Error(int errorCode, std::string msg);
    int GetErrorCode();
    std::string GetErrorMessage();
    std::string GetMessageForClient();

  private:
    std::string msg;
    int code;
  };
}  // internal
}  // recharged

#endif
