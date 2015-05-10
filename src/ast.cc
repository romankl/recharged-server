#include "ast.h"

namespace recharged {
namespace internal {

Ast::Ast() {
  this->first = NULL;
}


Ast::Ast(Node* first) {
  this->first = first;
}

void Ast::SetFirst(Node* node) {
    this->first = node;
}

Node* Ast::GetFirst() {
  return this->first;
}


void Ast::SetType(int type) {
  this->type = type;
}


int Ast::GetType() {
  return this->type;
}


}  // internal
}  // recharged
