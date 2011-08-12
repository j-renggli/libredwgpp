#include "dictionary.h"

#include "../version.h"

namespace libredwg2 {

namespace parserobject {

////////////////////////////////////////////////////////////////

// P. 142
core::ResultCode Dictionary::restoreFull(Schema& schema, DWGBuffer& buffer, const Version& version) const
{
  size_t numItems = buffer.readBit32();
//  LOG_DEBUG("Num items " << numItems);

  if (version.equals(Version::R14))
  {
    buffer.readRaw8();
  } else if (version.isAtLeast(Version::R2000)) {
    /*size_t cloningFlag = */buffer.readBit16();
    /*size_t ownerFlag = */buffer.readRaw8();
//    LOG_DEBUG("Cloning " << cloningFlag << " owner " << ownerFlag);
  }

  for (size_t item = 0; item < numItems; ++item)
  {
    UnicodeString strItem = buffer.readText(version);
//    LOG_DEBUG(strItem);
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
