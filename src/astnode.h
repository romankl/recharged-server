#ifndef _SRC_ASTNODE_H_
#define _SRC_ASTNODE_H_

#include <stdlib.h>
#include <iostream>
#include <string>

#include "node.h"

namespace recharged {
namespace internal {

  class AstCommandNode : public Node {
    std::string command;
  };

  class AstDataNode : public Node {

  };
}  // internal
}  // recharged

#endif
