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

  if (inputType == -1) {
    this->SetParserError();
    return NULL;
  }

  this->ParserTree(ast, inputType);
}


void Parser::ParserTree(Ast* ast, int inputType) {
  if (inputType == Protocol::kProtocolTypeSimpleString)
    this->ParseSimpleString(ast, 1);
  else if (inputType == Protocol::kProtocolTypeInteger)
    this->ParseInteger(ast, 1);
  else if (inputType == Protocol::kProtocolTypeError)
    this->ParseError(ast, 1);
  else if (inputType == Protocol::kProtocolTypeArray)
    this->ParserArray(ast);
  else
    this->SetParserError();
}


void Parser::ParserArray(Ast* ast) {
  // The number of elements in the array is always provided at the 2nd position
  int elements = this->input[1];
  int protocolHeader = -1;
  for (int i = 1; i <= elements; i++) {
    protocolHeader = this->ParseProtocolTypeToken(input[this->currentPos] + 2);
    this->ParserTree(ast, protocolHeader);
  }
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

  this->currentPos = i;

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


int Parser::EvaluteHeader(Ast* ast, int pos) {
  const char headerToken = this->input[pos];
  int resolvedToken = this->ParseProtocolTypeToken(headerToken);
  ast->SetType(resolvedToken);

  if (resolvedToken < 0)
    return -1;

  this->currentPos = 1;
  return resolvedToken;
}


int Parser::EvaluteHeader(Ast* ast) {
  return this->EvaluteHeader(ast, 0);
}
}  // namespace internal
}  // namespace recharged
