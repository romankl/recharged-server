#include "queue-header.h"

namespace recharged {
namespace internal {

QueueHeader::QueueHeader(Queue* queue) {
  this->queue = queue;
  this->created = uv_hrtime();
  this->totalCount = 0;
}

}  // namespace internal
}  // namespace recharged
