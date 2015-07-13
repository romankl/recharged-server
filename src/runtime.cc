#include "runtime.h"

namespace recharged {
namespace internal {

Runtime::Runtime() {
}

/*
 * Main Runtime function. Every input buffer from the uv callback gets executed
 * in this routine.
 * The parser will build up a "pseudo" ast using the buffer input. Using the Ast
 * it's possible for the runtime to evaluate the REPS commands and execute them.
 *
 * *Note* Only "native" RESP commands are executed here. JS REPS commands are
 * executed in the recharged::internal::JSRuntime using spidermonkey.
 *
 * Runtime results are returned back to the eventloop.
 */
std::string Runtime::Run(char *input) {
  Parser* parser = new Parser(input);
  Ast* ast =  parser->Parse();

  if (ast == nullptr) {
    return "+Error while execution";
  }

  Node* node = ast->GetFirst();
  if (node == nullptr)
    return "";

  while (node != nullptr) {
    std::string cmd = node->GetData();

    // Server::GetInstance().cmdMap->mapped[cmd](ast);



    node = node->GetNext();
  }


  delete parser;
  delete ast;

  // return the result so that it gets sent back to the client.
  return "";
}

}  // namespace internal
}  // namespace recharged
