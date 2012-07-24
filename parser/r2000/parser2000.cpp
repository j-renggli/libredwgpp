#include "parser2000.h"

#include <file/archive.h>

#include "../dwgbuffer.h"

namespace libredwgpp {

////////////////////////////////////////////////////////////////

Parser2000::Parser2000(Archive& archive) :
Parser(archive)
{
  version_.setRelease(Version::R2000);
}

////////////////////////////////////////////////////////////////

Parser2000::~Parser2000()
{
}

////////////////////////////////////////////////////////////////

boost::shared_ptr<Decoder> Parser2000::getDecoder(int method)
{
  LOG_ERROR("TODO");
  return boost::shared_ptr<Decoder>();
//  return boost::shared_ptr<Decoder2004_2>(new Decoder2004_2);
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2000::getSectionBuffer(Section::Type st, DWGBuffer& buffer)
{
  size_t index = size_t(-1);
  switch (st)
  {
    case Section::Classes:
      index = CLASS;
      break;
    case Section::Objects:
      index = OBJECT;
      break;
    default:
      break;
  }

  if (index >= vPages_.size())
  {
    LOG_ERROR("Section " << st << " not found");
    return core::rcFailure;
  }

//LOG_DEBUG("Address " << std::hex << vPages_[index].offset_);
//LOG_DEBUG("Size " << vPages_[index].size_);
//LOG_DEBUG("End     " << std::hex << (vPages_[index].offset_ + vPages_[index].size_));

  buffer.setPosition(0);
  return archive_.read(buffer.getBuffer(), vPages_[index].offset_, vPages_[index].size_);
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2000::parseFileHeader()
{
  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2000::parseInfo()
{
//  if (ptrMap_ == NULL)
//  {
//    LOG_ERROR("No section map to be found");
//    return core::rcFailure;
//  } else if (ptrInfo_ != NULL) {
//    LOG_ERROR("Section info already exists");
//    return core::rcFailure;
//  }
//
//  const Page* pPage = ptrMap_->findPage(id);
//  if (pPage == NULL)
//  {
//    LOG_ERROR("Could not find section info with id " << id);
//    return core::rcFailure;
//  }
//
//  ptrInfo_.reset(new SectionInfo(archive_, *pPage));
//  return ptrInfo_->restore();
  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2000::parseMap()
{
  // Go to just after revision number
  core::MemBuffer buffer;
  core::ResultCode rc = archive_.read(buffer, 21, 4);
  if (rc.isFailure())
    return rc;

  size_t maxRecords = buffer.read<uint32_t>(false);
  rc = archive_.read(buffer, 25, 9 * maxRecords);
  if (rc.isFailure())
    return rc;

  for (size_t i = 0; i < maxRecords; ++i)
  {
    Page page;
    page.id_ = buffer.read<uint8_t>(false);
    page.offset_ = buffer.read<uint32_t>(false);
    page.size_ = buffer.read<uint32_t>(false);

    vPages_.push_back(page);
//    LOG_DEBUG((uint16_t)page.id_ << " " << std::hex << page.offset_ << " " << page.size_);
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2000::parseObjects(ISchema& schema, ObjectsParser& parser)
{
  if (ptrClasses_ == NULL)
  {
    LOG_ERROR("Classes not parsed");
    return core::rcFailure;
  }
//  ptrObjects_.reset(new ObjectsParser(version_));

  DWGBuffer buffer;
  core::ResultCode rc = getSectionBuffer(Section::Objects, buffer);
  if (rc.isFailure())
    return rc;

  DWGBuffer objectData;

//  return ptrObjects_->restore(buffer);
  while (true)
  {
    size_t start = buffer.getPosition();

    uint32_t sgdc0 = buffer.readRaw8();
    uint32_t sgdc1 = buffer.readRaw8();
    uint32_t sectionSize = (sgdc0 << 8) | sgdc1;
//    LOG_DEBUG("Section size " << sectionSize << " start " << start);// LOG_DEBUG((data.getPosition() - start));
    uint32_t address = 0;
    while (buffer.getPosition() - start < sectionSize)
    {
      int asdf = buffer.readModularChar();
      int addroff = buffer.readModularChar();
      address += addroff;
//      LOG_DEBUG("pvztkt " << asdf << " pvzadr " << addroff << " means " << address);

      objectData.setPosition(0);
      rc = archive_.read(objectData.getBuffer(), address, 4096, false);
      if (rc.isFailure())
        return rc;

      rc = parser.restoreObject(schema, objectData, *ptrClasses_);
      if (rc.isFailure())
        return core::rcSuccess;
//        return rc;
    }

    buffer.skipBits();
    sgdc0 = buffer.readRaw8();
    sgdc1 = buffer.readRaw8();
    uint32_t ckr = (sgdc0 << 8) | sgdc1;

    if (sectionSize <= 2)
      break; //TODO
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}
