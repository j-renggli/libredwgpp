#include "entity.h"

#include <parser/version.h>

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

core::ResultCode Entity::restore(Schema& schema, DWGBuffer& buffer, const Version& version) const
{
//  LOG_DEBUG("entity");
//LOG_DEBUG(buffer.getPosition() << ", " << buffer.getOffset());
  bool hasGraphic = buffer.readBit();
//  LOG_DEBUG("pic " << hasGraphic);
  if (hasGraphic)
  {
//    LOG_DEBUG("Graphic");
    uint64_t graphicSize = 0;
    if (version.isAtLeast(Version::R2010))
    {
      graphicSize = buffer.readBit64();
    } else {
      graphicSize = buffer.readRaw32();
    }

    LOG_ERROR("Todo: parse or skip graphic data");
    return core::rcFailure;
  }

  if (version.isBetween(Version::R13, Version::R14))
  {
    /*size_t bitSize =*/ buffer.readRaw32();
//    size_t flags = buffer.readBit6();
//    size_t params = buffer.readBit6();

//    LOG_DEBUG("bitsize " << bitSize);
//    LOG_DEBUG(bitSize << "." << flags << "." << params);
  }

  int mode = buffer.readBit2();
  int numReac = buffer.readBit32();

  if (version.isAtLeast(Version::R2004))
  {
    buffer.readBit();
  }

  if (version.isBetween(Version::R13, Version::R14))
  {
    buffer.readBit();
  }

  bool hasLinks = ~buffer.readBit();

  Colour colour = buffer.readColour(version, true);
//  if (version.isAtLeast(Version::R2004))
//  {
//    if (hasLinks)
//    {
//      bool colourMode = buffer.readBit();
//      if (colourMode)
//      {
//        colour.setIndex(buffer.readRaw8());
//      } else {
//        size_t flags = buffer.readRaw16();
//        if (flags & 0x8000)
//        {
//          // TODO: doc says BS of 24 bits for RGB  !?
//          int r = buffer.readRaw8();
//          int g = buffer.readRaw8();
//          int b = buffer.readRaw8();
//          int a = buffer.readRaw8();
//          UnicodeString strName = buffer.readText(version);
//
//          colour.setRGBA(r, g, b, a);
//          colour.setName(strName);
//        }
//
//        if (flags & 0x4000)
//        {
//        }
//
//        if (flags & 0x2000)
//        {
//          int transparency = buffer.readBit32();
//        }
//      }
//    } else {
//      buffer.readBit();
//    }
//  } else {
//    colour = buffer.readColour(version);
//  }
//  ent->linetype_scale = bit_read_BD(dat);

//  Colour colour = data.readColour();
  double lineScale = buffer.readBitDouble();

  if (version.isAtLeast(Version::R2000))
  {
    int lineFlags = buffer.readBit2();
    int plotFlags = buffer.readBit2();
//    LOG_DEBUG(lineFlags << " / " << plotFlags);
  }

  if (version.isAtLeast(Version::R2007))
  {
    int materialFlags = buffer.readBit2();
    int shadowFlags = buffer.readRaw8();
  }

  int invisible = buffer.readBit16();

  if (version.isAtLeast(Version::R2000))
  {
    int lineWeight = buffer.readRaw8();
//    LOG_DEBUG(lineWeight);
  }

//  LOG_DEBUG(mode << " " << numReac << " " << hasLinks << " " << colour.index_ << " " << std::fixed << std::setprecision(6) << lineScale << " " << invisible);
//
//  return core::rcSuccess;
//LOG_DEBUG(buffer.getPosition() << ", " << buffer.getOffset());

  return restoreFull(schema, buffer, colour, version);
}

////////////////////////////////////////////////////////////////

}

}
