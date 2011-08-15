#include "layer.h"

#include "../version.h"

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

// P. 142
core::ResultCode Layer::restoreFull(Schema& schema, DWGBuffer& buffer, const Version& version) const
{
  UnicodeString strLayerName = buffer.readText(version);
//  LOG_DEBUG(strLayerName);
  /*bool flag64 = */buffer.readBit();
//  LOG_DEBUG(flag64);
  /*int xrefindex = */buffer.readBit16();// - 1;
//  LOG_DEBUG(xrefindex);

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
