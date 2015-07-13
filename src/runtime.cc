#include "runtime.h"
#include "server.h"

namespace recharged {
namespace internal {

Runtime::Runtime() {
}


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

    Server::GetInstance().cmdMap->mapped[cmd](ast, nullptr);



    node = node->GetNext();
  }


  delete parser;
  delete ast;

  // return the result so that it gets sent back to the client.
  return "";
}

}  // namespace internal
}  // namespace recharged
