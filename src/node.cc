#include "node.h"


namespace recharged {
namespace internal {
Node::Node(std::string data, int type) {
  this->data = data;
  this->type = type;
}


void Node::SetNext(Node* next) {
  this->next = next;
}


Node* Node::GetNext() {
  return this->next;
}
}  // internal
}  // recharged
