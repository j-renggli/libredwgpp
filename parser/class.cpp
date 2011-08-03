#include "class.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Class::Class(size_t id, uint16_t flags, const UnicodeString& strAppName, const UnicodeString& strCppName,
      const UnicodeString& strDxfName, bool wasZombie, size_t itemClassID) :
id_(id),
flags_(flags),
strAppName_(strAppName),
strCppName_(strCppName),
strDxfName_(strDxfName),
wasZombie_(wasZombie),
itemClassID_(itemClassID)
{
}

////////////////////////////////////////////////////////////////

}
