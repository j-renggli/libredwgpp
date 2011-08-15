#include "blockcontrol.h"

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

// P. 149
core::ResultCode BlockControl::restoreFull(ISchema& schema, DWGBuffer& buffer, const Version& version) const
{
  /*size_t numEntries =*/ buffer.readModularShort();
//  LOG_DEBUG("Num entries " << numEntries);

  Handle handle = buffer.readHandle();
//  LOG_DEBUG("handle " << (int16_t)handle.code_ << " " << handle.value_);

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
