#include "error.h"

namespace recharged {
namespace internal {

Error::Error(int errorCode, std::string msg) {
  this->msg = msg;
  this->code = code;
}


int Error::GetErrorCode() {
    return this->code;
}


std::string Error::GetMessageForClient() {
  return "-" + std::to_string(this->code) + " " + this->msg;
}


std::string Error::GetErrorMessage() {
  return this->msg;
}


}  // namespace internal
}  // namespace recharged
