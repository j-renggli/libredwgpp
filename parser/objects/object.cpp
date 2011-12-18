#include "object.h"

#include <parser/version.h>

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

core::ResultCode Object::restore(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const
{
//  LOG_DEBUG("object");

  if (version.isBetween(Version::R13, Version::R14))
  {
    /*size_t bitSize = */buffer.readRaw32();
  }

    /*size_t numReactors = */buffer.readBit32();

  if (version.isAtLeast(Version::R2004))
  {
    /*bool noXDictionaryHandler = */buffer.readBit();
  }

  return restoreFull(schema, buffer, handle, version);
}

////////////////////////////////////////////////////////////////

}

}
