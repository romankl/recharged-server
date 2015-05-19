#ifndef _SRC_AST_H_
#define _SRC_AST_H_

#include <stdlib.h>
#include "node.h"

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
      void AddNext(Node* next);

    private:
      long count;
      int type;
      Node* first;
      Node* last;
  };
}  // internal
}  // recharged

#endif
