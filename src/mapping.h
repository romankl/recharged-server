#ifndef _SRC_MAPPING_H_
#define _SRC_MAPPING_H_

#include <unordered_map>
#include <string>


namespace recharged {
namespace internal {

  template <class T>
  class Mapping {

    public:
      T Add(const std::string key, T cmd);
      T Get(const std::string key);
      std::unordered_map<std::string, T> mapped;

    private:
    };

}  // internal
}  // recharged


#endif
