#ifndef _SRC_PARSER_H_
#define _SRC_PARSER_H_

#include <iostream>
#include <stdlib.h>
#include <string>

#include "ast.h"
#include "error.h"
#include "protocol.h"


namespace recharged {
namespace internal {
  class Ast;
  class Error;

  class Parser {
  public:
    Parser(const char* input);
    Parser(){};

    void SetInput(const char* input);
    void SetInput(std::string input);
    Ast* Parse();

    Error HasError();
  private:
    const char* input;
    long length;
    int inputProtocolType;

    Error* error;
    int EvaluteHeader(Ast *ast);
    int ParseProtocolTypeToken(char token);
    void ParseSimpleString(Ast* ast, int start);
    void UpdateLength();
  };
}  // internal
}  // recharged

#endif
