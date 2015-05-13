#include "ast.h"

namespace recharged {
namespace internal {

Ast::Ast() {
  this->first = nullptr;
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


void Ast::AddNext(Node* next) {
  if (this->first == nullptr) {
    this->first = next;
    this->last = next;
    return;
  }

  Node* last = this->last;
  last->SetNext(next);
}


}  // internal
}  // recharged
