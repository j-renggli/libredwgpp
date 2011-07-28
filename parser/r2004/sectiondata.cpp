#include "sectiondata.h"

namespace libredwg2 {

//const int32_t SectionData::s_guard = 0x4163003b;

////////////////////////////////////////////////////////////////

SectionData::SectionData()//Archive& archive, size_t offset) :
//Section2004(archive, offset)
{
}

////////////////////////////////////////////////////////////////

core::ResultCode SectionData::restoreData(core::IReadBuffer& buffer)
{
  int32_t numDesc = buffer.read<int32_t>(false);
//  int32_t x02 = buffer.read<int32_t>(false);
//  int32_t x7400 = buffer.read<int32_t>(false);
//  int32_t x00 = buffer.read<int32_t>(false);
//  int32_t xODA = buffer.read<int32_t>(false);

  LOG_DEBUG("numDesc " << numDesc);
//  LOG_DEBUG("x02 " << x02);
//  LOG_DEBUG("x7400 " << x7400);
//  LOG_DEBUG("x00 " << x00);
//  LOG_DEBUG("xODA " << xODA);

  size_t next = 0x14;

  for (int desc = 0; desc < numDesc; ++desc)
  {
    buffer.setPosition(next);
    int64_t size = buffer.read<int64_t>(false);
    int32_t numPages = buffer.read<int32_t>(false);
    buffer.setPosition(next + 0x14);
    int32_t isCompressed = buffer.read<int32_t>(false); // 1 = no, 2 = yes
    int32_t sectionID = buffer.read<int32_t>(false);
    int32_t isEncrypted = buffer.read<int32_t>(false); // 0 = no, 1 = yes, 2 = unknown
    char psName[64];
    memcpy(psName, &buffer.getBuffer()[next + 0x20], 64);
    buffer.setPosition(next + 0x20 + 64);

    LOG_DEBUG(desc << ": (" << (isCompressed == 2) << "/" << (isEncrypted == 1) << " " << size << ") - " << sectionID << " " << psName << " [" << numPages << "]");

    for (int page = 0; page < numPages; ++page)
    {
      int32_t pageNum = buffer.read<int32_t>(false);
      int32_t dataSize = buffer.read<int32_t>(false);
      int64_t pageOffset = buffer.read<int64_t>(false);

      LOG_DEBUG(pageNum << " " << dataSize << " " << pageOffset);
    }

    next = buffer.getPosition();
  }
}

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////

}
