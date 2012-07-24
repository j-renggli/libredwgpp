#include "block.h"

#include "../version.h"

#include <schema/schema.h>

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

// P. 108
core::ResultCode Block::restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const
{
  schema.blockStart(handle.getValue(), buffer.readText(version));

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

// P. 108
core::ResultCode EndBlock::restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const
{
  LOG_WARNING(handle.getCode() << ", " << handle.getValue());
  schema.blockEnd();
//  LOG_DEBUG("End");

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

// P. 149
core::ResultCode BlockControl::restoreFull(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const
{
//  /*size_t numEntries =*/ buffer.readModularShort();
////  LOG_DEBUG("Num entries " << numEntries);
//
//  Handle h = buffer.readHandle();
////  LOG_DEBUG("handle " << (int16_t)handle.code_ << " " << handle.value_);

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

// P. 150
core::ResultCode BlockHeader::restoreFull(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const
{
//  LOG_WARNING(handle.getValue());
  UnicodeString strName = buffer.readText(version);
  bool flag = buffer.readBit();
  int xref = buffer.readBit16() - 1;
  bool xdep = buffer.readBit();
  bool anonymous = buffer.readBit();
  bool hasattr = buffer.readBit();
  bool isxref = buffer.readBit();
  bool isoverlaidxref = buffer.readBit();

  if (version.isAtLeast(Version::R2000))
    bool loadedbit = buffer.readBit();

  if (version.isAtLeast(Version::R2004))
  {
    size_t owned = buffer.readBit32();
  }

  const double baseX = buffer.readBitDouble();
  const double baseY = buffer.readBitDouble();
  const double baseZ = buffer.readBitDouble();
  UnicodeString strPathName = buffer.readText(version);
//  LOG_DEBUG(strName << " - " << strPathName << " [" << baseX << ", " << baseY << ", " << baseZ << "]");

  if (version.isAtLeast(Version::R2000))
  {
    int tot = 0;
    while (true)
    {
      size_t insertcount = buffer.readRaw8(); // TODO: Read until insertcount == 0???
      if (insertcount == 0)
        break;
      ++tot;
    }
    UnicodeString strDescription = buffer.readText(version);
    const uint32_t previewSize = buffer.readBit32();
    buffer.skipBytes(previewSize);

    if (version.isAtLeast(Version::R2007)) {
      const int16_t insertUnits = buffer.readBit16();
      const bool isExplodable = buffer.readBit();
      const char blockScaling = buffer.readRaw8();
      LOG_WARNING(insertUnits << ".. " << isExplodable << " " << blockScaling);
    }

    Handle handleRefs = buffer.readHandle();
//    LOG_WARNING(tot << " " << strDescription << ": " << previewSize);
//    LOG_WARNING(handleRefs.getCode() << ": " << handleRefs.getValue());
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
