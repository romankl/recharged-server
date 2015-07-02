#include "mapping.h"

namespace recharged {
namespace internal {

template <class T>
T Mapping<T>::Add(const std::string key, T cmd) {
  mapped[key] = cmd;
}

template <class T>
T Mapping<T>::Get(const std::string key) {
  return mapped[key];
}

}  // internal
}  // recharged
