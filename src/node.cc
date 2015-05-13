#include "node.h"


namespace recharged {
namespace internal {

Node::Node(int type, std::string data) {
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
