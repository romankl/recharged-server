#ifndef _SRC_RUNTIME_H_
#define _SRC_RUNTIME_H_

#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "ast.h"
#include "node.h"

namespace recharged {
namespace internal {

  class Runtime {
  public:
    Runtime();

    std::string Run(char *input);
  private:
  };
}  // internal
}  // recharged

#endif
