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


std::string Node::GetData() {
  return this->data;
}


int Node::GetType() {
  return this->type;
}

}  // internal
}  // recharged
