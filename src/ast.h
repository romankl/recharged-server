#ifndef _SRC_Ast_H_
#define _SRC_Ast_H_

#include <stdlib.h>

namespace recharged {
namespace internal {
  class Node;

  class Ast {
    public:
      Ast();
      Ast(Node* first);
      void SetFirst(Node *);
      Node* GetFirst();
      void SetType(int type);
      int GetType();

    private:
      long count;
      int type;
      Node* first;
  };
}  // internal
}  // recharged

#endif
