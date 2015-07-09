#include "request.h"

namespace recharged {
namespace internal {

Request::Request(Ast* ast, uv_buf_t* buffer) {
  this->ast = ast;
  this->buf = buffer;
}


uv_buf_t* GetResponseBuffer() {
  return this->buf;
}


Ast* GetAst() {
  return this->ast;
}


}  // internal
}  // recharged
