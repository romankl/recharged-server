#ifndef _SRC_QUEUE_H_
#define _SRC_QUEUE_H_

#include <stdlib.h>
#include <string>

#include "mapping.h"

namespace recharged {
namespace internal {

class QueueElement {
  public:
    QueueElement(std::string msg, std::string origin);
    void SetPrevElement(QueueElement* prev);
  private:
    QueueElement* prevElement;
    std::string msg;
    std::string id;
    std::string origin;
    Mapping* payload;
};

class Queue
{
  public:
    Queue();

    std::string GetId();
    std::string GetName();

    bool Delete();

    int GetCount();
    void IncrementCount();
    void DecrementCount();

    QueueElement* GetNextElement();
  private:
    std::string id;
    std::string name;
    int count;

    QueueElement* next;
};

}  // internal
}  // recharged

#endif
