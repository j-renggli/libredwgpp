#include "face3d.h"

#include "../version.h"

#include <schema/face3d.h>
#include <schema/schema.h>

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

// P. 124
core::ResultCode Face3D::restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Version& version) const
{
  libredwgpp::Vertex3d corners[4];
  uint16_t invisibleEdgeFlag = 0;

  if (version.isAtLeast(Version::R2000))
  {
    bool hasFlag = ~buffer.readBit();
    bool skipZ = buffer.readBit();
    double x = buffer.readRawDouble();
    double y = buffer.readRawDouble();
    double z = 0;
    if (!skipZ)
    {
      z = buffer.readRawDouble();
    }

    corners[0] = libredwgpp::Vertex3d(x, y, z);

    for (int i = 0; i < 3; ++i)
    {
      buffer.readBitDouble(x);
      buffer.readBitDouble(y);
      buffer.readBitDouble(z);
      corners[i + 1] = libredwgpp::Vertex3d(x, y, z);
    }

    if (hasFlag)
    {
      invisibleEdgeFlag = buffer.readBit16();
    }
  } else {
    libredwgpp::Vertex3d corners[4];

    for (int i = 0; i < 4; ++i)
    {
      double x = buffer.readBitDouble();
      double y = buffer.readBitDouble();
      double z = buffer.readBitDouble();
      corners[i] = libredwgpp::Vertex3d(x, y, z);
    }

    invisibleEdgeFlag = buffer.readBit16();
  }

  schema.addFace3d(libredwgpp::Face3d(colour, corners[0], corners[1], corners[2], corners[3]));

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
