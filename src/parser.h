#ifndef _SRC_PARSER_H_
#define _SRC_PARSER_H_

#include <stdlib.h>
#include <string.h>
#include "ast.h"

namespace recharged {
namespace internal {
  class Ast;

  class Parser {
  public:
    Parser(const char* input);
    Ast* parse();
  private:
    const char* input;
    long length;

    int evaluteHeader(Ast *ast);
  };
}  // internal
}  // recharged

#endif
