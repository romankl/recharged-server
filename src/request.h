#ifndef _SRC_REQUEST_H_
#define _SRC_REQUEST_H_

#include <stdlib.h>
#include <string>

#include "ast.h"
#include "uv.h"

namespace recharged {
namespace internal {

class Request {
  public:
    Request(Ast* ast, uv_buf_t* buffer);

    Ast* GetAst();
    uv_buf_t* GetResponseBuffer();

  private:
    uv_buf_t* buffer;
    Ast* ast;
};

}  // internal
}  // recharged

#endif
