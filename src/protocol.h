#ifndef _SRC_PROTOCOL_H_
#define _SRC_PROTOCOL_H_

#include <stdlib.h>
#include <string>

namespace recharged {
namespace internal {

  class Protocol {
  public:
    enum ProtocolType {
      kProtocolTypeError, // -
      kProtocolTypeBlukString, // $
      kProtocolTypeSimpleString, // +
      kProtocolTypeInteger,  // :
      kProtocolTypeArray // *
    };

    enum ProtocolSign {
      kProtocolSignError = '-',
      kProtocolSignBulkString = '$',
      kProtocolSignSimpleString = '+',
      kProtocolSignInteger = ':',
      kProtocolSignArray = '*'
    };
  private:
  };
}  // internal
}  // recharged

#endif
