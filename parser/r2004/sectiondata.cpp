#include "sectiondata.h"

namespace libredwg2 {

const int32_t SectionData::s_guard = 0x4163003b;

////////////////////////////////////////////////////////////////

SectionData::SectionData(Archive& archive, size_t offset) :
Section2004(archive, offset)
{
}

////////////////////////////////////////////////////////////////

core::ResultCode SectionData::restoreData(core::IReadBuffer& buffer)
{
//  // Parse section pages
////  std::vector<DataSection> vSections;
//  int next = 0x100;
//  while (clear.getPosition() < clear.getSize())
//  {
//    int32_t id = buffer.read<int32_t>(false);
//    int32_t size = buffer.read<int32_t>(false);
//    ASSERT(size >= 0); // TODO: negative values !!! Change the meaning of next !!!
//    mSections_[id] = SectionData(archive_, next);
//    next += size;
//
////    if (data.size_ < 0)
////    {
////      int parent = clear.read<int32_t>(false);
////      int left = clear.read<int32_t>(false);
////      int right = clear.read<int32_t>(false);
////      int x_what = clear.read<int32_t>(false);
////    }
//  }
}

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////

}
