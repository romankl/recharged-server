#include "queue.h"

namespace recharged {
namespace internal {

QueueElement::QueueElement(std::string msg, std::string origin) {
  this->msg = msg;
  this->origin = origin;
}


void QueueElement::SetPrevElement(QueueElement* prev) {
  this->prevElement = prev;
}


Queue::Queue() {
  this->name = "";
}


std::string Queue::GetId() {
  return this->id;
}


std::string Queue::GetName() {
  return this->name;
}


bool Queue::Delete() {
  // TODO
  return false;
}


int Queue::GetCount() {
  return this->count;
}


void Queue::IncrementCount() {
  this->count++;
}


void Queue::DecrementCount() {
  this->count--;
}


QueueElement* Queue::GetNextElement() {
    return this->next;
}


std::string QueueCommands::QueueCreateCommand(Ast* ast, uv_buf_t* buf) {
  int i = 0;
  i++;
  i = i;
}


}  // namespace internal
}  // namespace recharged
