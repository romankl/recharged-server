#ifndef _SRC_Ast_H_
#define _SRC_Ast_H_

namespace recharged {
namespace internal {
  class Node;

  class Ast {
    public:

      int type;
    private:
      long count;
      Node* first;
  };
}  // internal
}  // recharged

#endif
