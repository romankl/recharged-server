#include "parser.h"

namespace recharged {
namespace internal {



Parser::Parser(const char* input) {
  this->input = input;
  this->length = strlen(input);
}


Ast* Parser::parse() {
  Ast* ast = new Ast();
  if (evaluteHeader(ast) == 0) {

  } else {

  }
  return NULL;
}

int Parser::evaluteHeader(Ast* ast) {
  const char headerToken = this->input[0];

  if (headerToken == '*') {
    ast->type = Ast::kAstTypeArray;
    return 0;
  } else if (headerToken == '-') {
    ast->type = Ast::kAstTypeError;
    return 0;
  } else if (headerToken == '$') {
    ast->type = Ast::kAstTypeBlukArray;
    return 0;
  } else if (headerToken == ':') {
    ast->type = Ast::kAstTypeInteger;
    return 0;
  }

  return -1;
}
}  // namespace internal
}  // namespace recharged
