#include "sectioninfo.h"

#include "../dwgbuffer.h"

namespace libredwg2 {

const int32_t SectionInfo::s_guard = 0x4163003b;

////////////////////////////////////////////////////////////////

SectionInfo::SectionInfo(Archive& archive, const Page& single) :
Section2004(archive, single)
{
}

////////////////////////////////////////////////////////////////

const SectionInfo::Subsection* SectionInfo::findSubsection(Section::Type type) const
{
  SubsectionMap::const_iterator it = mSubsections_.find(type);
  if (it == mSubsections_.end())
    return NULL;

  return &it->second;
}

////////////////////////////////////////////////////////////////

core::ResultCode SectionInfo::restoreData(DWGBuffer& data)
{
  core::IReadBuffer& buffer = data.getBuffer();

  int32_t numDesc = buffer.read<int32_t>(false);
//  int32_t x02 = buffer.read<int32_t>(false);
//  int32_t x7400 = buffer.read<int32_t>(false);
//  int32_t x00 = buffer.read<int32_t>(false);
//  int32_t xODA = buffer.read<int32_t>(false);

//  LOG_DEBUG("numDesc " << numDesc);
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
    int32_t pageSize = buffer.read<int32_t>(false);
    buffer.setPosition(next + 0x14);
    int32_t isCompressed = buffer.read<int32_t>(false); // 1 = no, 2 = yes
    int32_t sectionID = buffer.read<int32_t>(false);
    int32_t isEncrypted = buffer.read<int32_t>(false); // 0 = no, 1 = yes, 2 = unknown
    char pszName[64];
    memcpy(pszName, &buffer.getBuffer()[next + 0x20], 63);
    pszName[63] = '\0';
    buffer.setPosition(next + 0x20 + 64);

//    LOG_DEBUG(desc << ": (" << (isCompressed == 2) << "/" << (isEncrypted == 1) << " " << size << ") - " << sectionID << " " << pszName << " [" << numPages << "]");
    std::vector<Page> vPages(numPages);

    for (int page = 0; page < numPages; ++page)
    {
      vPages[page].id_ = buffer.read<int32_t>(false);
      vPages[page].size_ = buffer.read<int32_t>(false);
      vPages[page].offset_ = buffer.read<uint32_t>(false);
      buffer.read<uint32_t>(false);


//      LOG_DEBUG(vPages[page].id_ << " " << vPages[page].size_ << " " << vPages[page].offset_);
    }

    Section::Type type = Section::findType(pszName);
    if (type != Section::Unknown)
    {
      mSubsections_.insert(std::make_pair(type, Subsection(sectionID, size, isCompressed == 2, isEncrypted == 1, pageSize, vPages)));
    }

    next = buffer.getPosition();
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

SectionInfo::Subsection::Subsection(int32_t id, int64_t size, bool isCompressed, bool isEncrypted, int32_t pageSize, const std::vector<Page>& vPages) :
id_(id),
pageSize_(pageSize),
size_(id),
isCompressed_(isCompressed),
isEncrypted_(isEncrypted),
vPages_(vPages)
{
}

////////////////////////////////////////////////////////////////

}
