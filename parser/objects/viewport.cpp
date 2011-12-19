#include "viewport.h"

#include "../version.h"

//#include <schema/face3d.h>
//#include <schema/schema.h>

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

// P. 164
core::ResultCode Viewport::restoreFull(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const
{
  UnicodeString strName = buffer.readText(version);
  bool bit1 = buffer.readBit();
  int xref = int(buffer.readBit16()) - 1;
  bool xdep = buffer.readBit();
  double viewHeight = buffer.readBitDouble();
  double aspectRatio = buffer.readBitDouble();
//  LOG_DEBUG(strName << " " << bit1 << " " << xref << " " << xdep << " " << viewHeight << ":" << aspectRatio);
  double centerX = buffer.readRawDouble();
  double centerY = buffer.readRawDouble();
  double targetX = buffer.readBitDouble();
  double targetY = buffer.readBitDouble();
  double targetZ = buffer.readBitDouble();
  double dirX = buffer.readBitDouble();
  double dirY = buffer.readBitDouble();
  double dirZ = buffer.readBitDouble();
  double twist = buffer.readBitDouble();
//  LOG_DEBUG("[" << centerX << ", " << centerY << "] (" << twist << ")");
//  LOG_DEBUG("[" << targetX << ", " << targetY << ", " << targetZ << "]");
//  LOG_DEBUG("[" << dirX << ", " << dirY << ", " << dirZ << "]");
  double lensLen = buffer.readBitDouble();
  double frontClip = buffer.readBitDouble();
  double backClip = buffer.readBitDouble();
  bool vm0 = buffer.readBit();
  bool vm1 = buffer.readBit();
  bool vm2 = buffer.readBit();
  bool vm4 = buffer.readBit();
//  LOG_DEBUG(lensLen << " " << frontClip << " " << backClip << " " << vm0 << " " << vm1 << " " << vm2 << " " << vm4);

  if (version.isAtLeast(Version::R2000))
  {
    int rendermode = buffer.readRaw8();
//    LOG_DEBUG(rendermode);
  }

  if (version.isAtLeast(Version::R2007))
  {
    bool useDefaultLights = buffer.readBit();
    int deflig = buffer.readRaw8();
    double brightness = buffer.readBitDouble();
    double contrast = buffer.readBitDouble();
    Colour ambient = buffer.readColour(version, false);
  }

  double lowerLeftX = buffer.readRawDouble();
  double lowerLeftY = buffer.readRawDouble();
  double upperRightX = buffer.readRawDouble();
  double upperRightY = buffer.readRawDouble();
//  LOG_DEBUG("[" << lowerLeftX << ", " << lowerLeftY << "] [" << upperRightX << ", " << upperRightY << "]");
  bool vm3 = buffer.readBit();
  int zoom = buffer.readBit16();
  bool fastZoom = buffer.readBit();
  bool icon0 = buffer.readBit();
  bool icon1 = buffer.readBit();
  bool gridOn = buffer.readBit();
  double gridSpacingX = buffer.readRawDouble();
  double gridSpacingY = buffer.readRawDouble();
//  LOG_DEBUG("[" << gridSpacingX << ", " << gridSpacingY << "]");
  bool snapOn = buffer.readBit();
  bool snapStyle = buffer.readBit();
  int snapisopair = buffer.readBit16();
  double snaprot = buffer.readBitDouble();
  double snapBaseX = buffer.readRawDouble();
  double snapBaseY = buffer.readRawDouble();
  double snapSpaceX = buffer.readRawDouble();
  double snapSpaceY = buffer.readRawDouble();
//  LOG_DEBUG("[" << snapBaseX << ", " << snapBaseY << "] [" << snapSpaceX << ", " << snapSpaceY << "]");

  if (version.isAtLeast(Version::R2000))
  {
    buffer.readBit();
    bool ucsperview = buffer.readBit();
    double originX = buffer.readBitDouble();
    double originY = buffer.readBitDouble();
    double originZ = buffer.readBitDouble();
    double ucsXX = buffer.readBitDouble();
    double ucsXY = buffer.readBitDouble();
    double ucsXZ = buffer.readBitDouble();
    double ucsYX = buffer.readBitDouble();
    double ucsYY = buffer.readBitDouble();
    double ucsYZ = buffer.readBitDouble();
    double ucselevation = buffer.readBitDouble();
    int ucsorthotype = buffer.readBit16();
//    LOG_DEBUG("Origin [" << originX << ", " << originY << ", " << originZ << "]");
//    LOG_DEBUG("[" << ucsXX << ", " << ucsXY << ", " << ucsXZ << "]");
//    LOG_DEBUG("[" << ucsYX << ", " << ucsYY << ", " << ucsYZ << "]");
  }

  if (version.isAtLeast(Version::R2007))
  {
    int gridflag = buffer.readBit16();
    int gridmajor = buffer.readBit16();
  }

  Handle handlerefs = buffer.readHandle();
//  LOG_DEBUG(handle.getCode() << ": " << handle.getValue());

  if (version.isAtLeast(Version::R2007))
  {
    Handle bghandle = buffer.readHandle();
    Handle vshandle = buffer.readHandle();
    Handle sunhandle = buffer.readHandle();
  }

  if (version.isAtLeast(Version::R2000))
  {
    Handle namedUCShandle = buffer.readHandle();
    Handle baseUCShandle = buffer.readHandle();
//  LOG_DEBUG(namedUCShandle.getCode() << ": " << namedUCShandle.getValue());
//  LOG_DEBUG(baseUCShandle.getCode() << ": " << baseUCShandle.getValue());
  }

//  return core::rcFailure;

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
