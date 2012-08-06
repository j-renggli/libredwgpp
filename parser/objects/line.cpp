#include "line.h"

#include "../version.h"
#include "../../schema/schema.h"
#include "../../schema/vertex3d.h"

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

// P. 116
core::ResultCode Line::restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const
{
  Vertex3d start;
  Vertex3d end;
  if (version.isBetween(Version::R13, Version::R14)) {
    start.set(0, buffer.readBitDouble());
    start.set(1, buffer.readBitDouble());
    start.set(2, buffer.readBitDouble());
    end.set(0, buffer.readBitDouble());
    end.set(1, buffer.readBitDouble());
    end.set(2, buffer.readBitDouble());
  } else if (version.isAtLeast(Version::R2000)) {
    const bool zzero = buffer.readBit();
    double temp = buffer.readRawDouble();
    start.set(0, temp);
    buffer.readBitDouble(temp);
    end.set(0, temp);
    temp = buffer.readRawDouble();
    start.set(1, temp);
    buffer.readBitDouble(temp);
    end.set(1, temp);
    if (!zzero) {
      temp = buffer.readRawDouble();
      start.set(2, temp);
      buffer.readBitDouble(temp);
      end.set(2, temp);
    }
  }

  double thickness = buffer.readBitThickness(version);
  double extX = 0.;
  double extY = 0.;
  double extZ = 0.;
  buffer.readBitExtrusion(version, extX, extY, extZ);

  schema.addLine(handle.getValue(), start, end, thickness, Vertex3d(extX, extY, extZ));

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
