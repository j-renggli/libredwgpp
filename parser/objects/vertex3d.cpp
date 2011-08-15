#include "vertex3d.h"

#include "../version.h"

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////
//int asdf = 0;
// P. 112

core::ResultCode Vertex3D::restoreFull(Schema& schema, DWGBuffer& buffer, const Colour& colour, const Version& version) const
{
  buffer.readRaw8();

  //std::cout << std::endl;
  //  for (int i = 0; i < 500; ++i)
  //  {
  //    bool bit = buffer.readBit();
  //    std::cout << (bit ? "1" : "0");
  //  }
  //std::cout << std::endl;
//  UnicodeString strShapeFileName = buffer.readText(version);
//  LOG_DEBUG(strShapeFileName);
//  bool flag64 = buffer.readBit();
//  LOG_DEBUG(flag64);
//  int xrefindex = buffer.readBit16() - 1;
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

//  LOG_DEBUG(++asdf);
//  if (asdf++ > 1)
//  return core::rcFailure;
  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
