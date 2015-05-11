#include "parser.h"

using namespace std;

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


void Parser::SetInput(string input) {
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
    this->SetParserError();
    return NULL;

  if (inputType == Protocol::kProtocolTypeSimpleString)
    this->ParseSimpleString(ast, 1);
  else if (inputType == Protocol::kProtocolTypeInteger)
    this->ParseInteger(ast, 1);
  else if (inputType == Protocol::kProtocolTypeError)
    this->ParseError(ast, 1);
  else
    this->SetParserError();
}


void Parser::SetParserError() {
  Error(0, "Coud not parse expression");
}


void Parser::ParseInteger(Ast *ast, int start) {
  string token = this->ParseSingleProtocolToken(start);
  // TODO: to Int conversion
  cout << "Parsed Integer: " << token << endl;
}


string Parser::ParseSingleProtocolToken(int start) {
  int i = 0;
  for (i = start; i < this->length; i++) {
    // End of the string: +OK\r\n (4 tokens left till the end of the end input)
    if ((i - 1) == (this->length - 4))
      break;

    if ((this->input[i] == '\r') && ((this->input[i + 1] == '\n')))
      break;
  }

  string token(input);
  token = token.substr(1, this->length - 2);
  return token;
}


void Parser::ParseSimpleString(Ast* ast, int start) {
  string token = this->ParseSingleProtocolToken(start);
  cout << "Parsed SimpleString: " << token << endl;
}


void Parser::ParseError(Ast *ast, int start) {
  string token = this->ParseSingleProtocolToken(start);
  cout << "Parsed Error: " << token << endl;
}


int Parser::ParseProtocolTypeToken(char token) {
    if (token == Protocol::kProtocolSignArray)
      return Protocol::kProtocolTypeArray;
    else if (token == Protocol::kProtocolSignError)
      return Protocol::kProtocolTypeError;
    else if (token == Protocol::kProtocolSignBulkString)
      return Protocol::kProtocolTypeBlukString;
    else if (token == Protocol::kProtocolSignInteger)
      return Protocol::kProtocolTypeInteger;
    else if (token == Protocol::kProtocolSignSimpleString)
      return Protocol::kProtocolTypeSimpleString;

    return -1;
}


int Parser::EvaluteHeader(Ast* ast) {
  const char headerToken = this->input[0];
  int resolvedToken = this->ParseProtocolTypeToken(headerToken);
  ast->SetType(resolvedToken);

  if (resolvedToken < 0)
    return -1;

  return resolvedToken;
}
}  // namespace internal
}  // namespace recharged
