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

    int EvaluteHeader(Ast *ast);
    int ParseProtocolTypeToken(char token);
    std::string ParseSingleProtocolToken(int start);
    void ParseSimpleString(Ast* ast, int start);
    void ParseInteger(Ast *ast, int start);
    void ParseError(Ast *ast, int start);
    void UpdateLength();
    void SetParserError();
  };
}  // internal
}  // recharged

#endif
