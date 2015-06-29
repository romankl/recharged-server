#ifndef _SRC_MAPPING_H_
#define _SRC_MAPPING_H_

#include <unordered_map>
#include <string>


namespace recharged {
namespace internal {

  class Mapping {

    public:
      void Add(const std::string key, void* cmd);
      void* Get(const std::string key);
    private:
      std::unordered_map<std::string, void*> mapped;
    };

}  // internal
}  // recharged


#endif
