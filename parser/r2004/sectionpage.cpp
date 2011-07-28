#include "sectionpage.h"

#include "sectiondata.h"

namespace libredwg2 {

//const int32_t SectionPage::s_guard = 0x41630e3b;

////////////////////////////////////////////////////////////////

SectionPage::SectionPage()//Archive& archive, size_t offset) :
//Section2004(archive, offset)
{
}

////////////////////////////////////////////////////////////////

core::ResultCode SectionPage::restoreData(core::IReadBuffer& buffer)
{
  // Parse section pages
//  std::vector<DataSection> vSections;
  int next = 0x100;
  while (buffer.getPosition() < buffer.getSize())
  {
    int32_t id = buffer.read<int32_t>(false);
    int32_t size = buffer.read<int32_t>(false);
    ASSERT(size >= 0); // TODO: negative values !!! Change the meaning of next !!!
    mSections_.insert(std::make_pair(id, Page(next)));

//LOG_DEBUG(id << " " << size << " " << next);
    next += size;

//    if (data.size_ < 0)
//    {
//      int parent = clear.read<int32_t>(false);
//      int left = clear.read<int32_t>(false);
//      int right = clear.read<int32_t>(false);
//      int x_what = clear.read<int32_t>(false);
//    }
  }

//  // TODO
//  SectionsMap::iterator it = mSections_.find(100);
////  LOG_DEBUG((it == mSections_.end()));
//  core::MemBuffer buf;
//  return it->second->restore();

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////
// Page
////////////////////////////////////////////////////////////////

SectionPage::Page::Page(int32_t offset) :
offset_(offset)
{
}

////////////////////////////////////////////////////////////////

}
