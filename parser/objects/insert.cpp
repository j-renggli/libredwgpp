#include "insert.h"

#include "../version.h"
#include <schema/schema.h>
#include <schema/vertex3d.h>

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////
// P. 109
//int asdf = 0;
core::ResultCode Insert::restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const
{
  const double translationX = buffer.readBitDouble();
  const double translationY = buffer.readBitDouble();
  const double translationZ = buffer.readBitDouble();
//  LOG_DEBUG("[" << translationX << ", " << translationY << ", " << translationZ << "]");

  double scaleX = 1.;
  double scaleY = 1.;
  double scaleZ = 1.;

  if (version.isBetween(Version::R13, Version::R14))
  {
    scaleX = buffer.readBitDouble();
    scaleY = buffer.readBitDouble();
    scaleZ = buffer.readBitDouble();
  }

  if (version.isAtLeast(Version::R2000))
  {
    int flags = buffer.readBit2();
    if (!(flags & 0x01))
    {
      scaleX = buffer.readRawDouble();
      scaleY = scaleX;
      scaleZ = scaleX;
    }

    if (!(flags & 0x02))
    {
      buffer.readBitDouble(scaleY);
      buffer.readBitDouble(scaleZ);
    }
  }
//    LOG_DEBUG("[" << scaleX << ", " << scaleY << ", " << scaleZ << "]");

  // Rotation + axis
  const double rotation = buffer.readBitDouble();
  const double axisX = buffer.readBitDouble();
  const double axisY = buffer.readBitDouble();
  const double axisZ = buffer.readBitDouble();
  LOG_ERROR(rotation << "[rad] [" << axisX << ", " << axisY << ", " << axisZ << "]");
  bool hasAttrib = buffer.readBit();
  LOG_ERROR("Has attribute " << hasAttrib);

  if (version.isAtLeast(Version::R2004))
  {
    int numObj = buffer.readBit32();
    LOG_DEBUG(numObj);
  }

  Handle h = buffer.readHandle();
  LOG_DEBUG("Handle: " << h.getCode() << " => " << h.getValue());

  schema.insert(h.getValue(), Vertex3d(axisX, axisY, axisZ), rotation,
                                 Vertex3d(scaleX, scaleY, scaleZ),
                                 Vertex3d(translationX, translationY, translationZ));
//LOG_ERROR(++asdf);
//if (++asdf > 138)
//return core::rcFailure;
  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
