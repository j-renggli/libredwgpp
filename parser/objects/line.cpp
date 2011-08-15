#include "line.h"

#include "../version.h"

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

// P. 112
core::ResultCode Line::restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Version& version) const
{
  UnicodeString strShapeFileName = buffer.readText(version);
//  LOG_DEBUG(strShapeFileName);
/*  bool flag64 = */buffer.readBit();
//  LOG_DEBUG(flag64);
/*  int xrefindex = */buffer.readBit16();// - 1;
//  LOG_DEBUG(xrefindex);
//  if (xrefindex >= 0)
//  {
//    bool xdep = buffer.readBit();
//    LOG_DEBUG(xdep);
//  }
//  bool isVertical = buffer.readBit();
//  LOG_DEBUG(isVertical);
//  bool isShapeFile = buffer.readBit();
//  LOG_DEBUG(isShapeFile);
//  double fixedHeight = buffer.readBitDouble();
//  LOG_DEBUG(fixedHeight);
//  double widthFactor = buffer.readBitDouble();
//  LOG_DEBUG(widthFactor);
//  double oblique = buffer.readBitDouble();
//  LOG_DEBUG(oblique);
//  size_t genFlags = buffer.readRaw8();
//  LOG_DEBUG(genFlags);
//  double lastHeight = buffer.readBitDouble();
//  LOG_DEBUG(lastHeight);

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
