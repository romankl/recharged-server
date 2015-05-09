#include "parser.h"

namespace recharged {
namespace internal {

Parser::Parser(const char* input) {
  this->input = input;
  this->length = strlen(input);
}


void Parser::SetInput(const char* input) {
  this->input = input;
  UpdateLength();
}


void Parser::SetInput(std::string input) {
  this->input = input.c_str();
  UpdateLength();
}


void Parser::UpdateLength() {
  this->length = strlen(this->input);
}


Ast* Parser::Parse() {
  Ast* ast = new Ast();
  int inputType = EvaluteHeader(ast);

  if (inputType == -1)
    return NULL;

  if (inputType == Protocol::kProtocolTypeSimpleString) {
    ParseSimpleString(ast, 1);
    fprintf(stderr, "");
  }
}


void Parser::ParseSimpleString(Ast* ast, int start) {
  int i = 0;
  for (i = start; i < this->length; i++) {
    // End of the string: +OK\r\n (4 tokens left till the end of the end input)
    if ((i - 1) == (this->length - 4))
      break;

    if ((this->input[i] == '\r') && ((this->input[i + 1] == '\n')))
      break;
  }

  std::string token(input);
  token = token.substr(1, this->length - 2);

  std::cout << "Parsed: " << token << std::endl;
}


int Parser::ParseProtocolTypeToken(char token) {
    if (token == Protocol::kProtocolSignArray)
      return Protocol::kProtocolTypeArray;
    else if (token == Protocol::kProtocolSignError)
      return Protocol::kProtocolTypeError;
    else if (token == Protocol::kProtocolSignBulkArray)
      return Protocol::kProtocolTypeBlukArray;
    else if (token == Protocol::kProtocolSignInteger)
      return Protocol::kProtocolTypeInteger;
    else if (token == Protocol::kProtocolSignSimpleString)
      return Protocol::kProtocolTypeSimpleString;

    return -1;
}


int Parser::EvaluteHeader(Ast* ast) {
  const char headerToken = this->input[0];
  int resolvedToken = this->ParseProtocolTypeToken(headerToken);
  ast->type = resolvedToken;

  if (resolvedToken < 0)
    return -1;

  return resolvedToken;
}
}  // namespace internal
}  // namespace recharged
