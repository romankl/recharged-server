#include "mapping.h"

namespace recharged {
namespace internal {

void Mapping::Add(const std::string key, void* cmd) {
  mapped[key] = cmd;
}


void* Mapping::Get(const std::string key) {
  return mapped[key];
}

}  // internal
}  // recharged
