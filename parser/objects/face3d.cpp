#include "face3d.h"

#include "../version.h"

#include <schema/face3d.h>
#include <schema/schema.h>

namespace libredwg2 {

namespace parserobject {

////////////////////////////////////////////////////////////////
int i = 0;
// P. 124
core::ResultCode Face3D::restoreFull(Schema& schema, DWGBuffer& buffer, const Colour& colour, const Version& version) const
{
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

    libredwg2::Vertex3d corners[4];
    corners[0] = libredwg2::Vertex3d(x, y, z);

    for (int i = 0; i < 3; ++i)
    {
      buffer.readBitDouble(x);
      buffer.readBitDouble(y);
      buffer.readBitDouble(z);
      corners[i + 1] = libredwg2::Vertex3d(x, y, z);
    }

    if (hasFlag)
    {
      buffer.readBit16();
    }

    schema.addFace3d(libredwg2::Face3d(colour, corners[0], corners[1], corners[2], corners[3]));
  } else {
    for (int i = 1; i < 5; ++i)
    {
      double x = buffer.readBitDouble();
      double y = buffer.readBitDouble();
      double z = buffer.readBitDouble();
  //    double x, y, z;
  //    buffer.readBitExtrusion(version, x, y, z);

      LOG_DEBUG("corner " << i << " : [" << x << ", " << y << ", " << z << "]");
      return core::rcFailure;
    }
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
