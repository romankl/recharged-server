#ifndef _SRC_QUEUE_HEADER_H_
#define _SRC_QUEUE_HEADER_H_

#include <stdlib.h>
#include <string>

#include "queue.h"
#include "uv.h"

namespace recharged {
namespace internal {

class QueueHeader
{
    public:
      QueueHeader(Queue* queue);
    private:
      unsigned int created;
      unsigned int totalCount;
      Queue* queue;
};

}  // internal
}  // recharged

#endif
