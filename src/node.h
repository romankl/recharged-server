#ifndef _SRC_NODE_H_
#define _SRC_NODE_H_

#include <string>

namespace recharged {
namespace internal {

  class Node {
    public:
      Node(std::string data, int type);
      void SetNext(Node* next);
      Node* GetNext();

      enum NodeType {
        kCommandNode,
        kDataNode
      };
    private:
      std::string data;
      int type;
      Node* next;
  };
}  // internal
}  // recharged

#endif
