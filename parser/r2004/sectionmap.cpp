#include "sectionmap.h"

#include "../dwgbuffer.h"

namespace libredwgpp {

const int32_t SectionMap::s_guard = 0x41630e3b;

////////////////////////////////////////////////////////////////

SectionMap::SectionMap(Archive& archive, const Page& single) :
Section2004(archive, single)
{
}

////////////////////////////////////////////////////////////////

const Page* SectionMap::findPage(int32_t id) const
{
  SectionsMap::const_iterator it = mSections_.find(id);
  if (it == mSections_.end())
    return NULL;

  return &it->second;
}

////////////////////////////////////////////////////////////////

core::ResultCode SectionMap::restoreData(DWGBuffer& data)
{
  core::IReadBuffer& buffer = data.getBuffer();

  // Parse section pages
//  std::vector<DataSection> vSections;
  int next = 0x100;
  while (buffer.getPosition() < buffer.getSize())
  {
    Page page;
    page.id_ = buffer.read<int32_t>(false);
    page.size_ = buffer.read<int32_t>(false);
    page.offset_ = next;
    ASSERT(page.size_ >= 0); // TODO: negative values !!! Change the meaning of next !!!
    mSections_.insert(std::make_pair(page.id_, page));

//    LOG_DEBUG(page.id_ << " " << page.size_ << " " << page.offset_);
//    if (data.size_ < 0)
//    {
//      int parent = clear.read<int32_t>(false);
//      int left = clear.read<int32_t>(false);
//      int right = clear.read<int32_t>(false);
//      int x_what = clear.read<int32_t>(false);
//    }
    next += page.size_;

  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}
