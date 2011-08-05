#include "parser2004.h"

#include "../dwgbuffer.h"
#include "decoder2004_2.h"
#include "sectioninfo.h"
#include "sectionmap.h"
#include "sectionobjects.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Parser2004::Parser2004(Archive& archive) :
Parser(archive)
{
  version_.setRelease(Version::R2004);
}

////////////////////////////////////////////////////////////////

Parser2004::~Parser2004()
{
}

////////////////////////////////////////////////////////////////

boost::shared_ptr<Decoder> Parser2004::getDecoder(int method)
{
  return boost::shared_ptr<Decoder2004_2>(new Decoder2004_2);
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2004::getSectionBuffer(Section::Type st, DWGBuffer& buffer)
{
  // If info, then map !
  if (ptrInfo_ == NULL)
  {
    LOG_ERROR("No section info to be found");
    return core::rcFailure;
  }

  const SectionInfo::Subsection* pClassSec = ptrInfo_->findSubsection(st);

  if (pClassSec == NULL)
  {
    LOG_ERROR("Could not find classes' subsection ");
    return rcSectionNotFound;
  }

  Decoder2004_2 decoder;
  core::ResultCode rc = decoder.decode(archive_, *ptrMap_, pClassSec->getPages(), buffer);
  buffer.setPosition(0);
  return rc;

//  switch (st)
//  {
//    case Section::Classes:
//      break;
//    default:
//      break;
//  }

  //TODO
  return core::rcFailure;

//
//  SectionClasses sc(archive_, pClassSec->getPages());
//  core::ResultCode rc = sc.restoreMultiple(*ptrMap_);
//  return rc;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2004::parseFileHeader()
{
  // Go to just after revision number
  core::MemBuffer buffer;
  core::ResultCode rc = archive_.read(buffer, 6, 122);
  if (rc.isFailure())
    return rc;

  buffer.setPosition(5);
  version_.setMaintenance(buffer.read<uint8_t>());
//  buffer.setPosition(7);
//  int32_t previewOffset = buffer.read<int32_t>(false);
//  buffer.setPosition(13);
//  int16_t codepage = buffer.read<int16_t>(false);
//  buffer.setPosition(18);
//  int32_t securityFlags = buffer.read<int32_t>(false);
//  buffer.setPosition(26);
//  int32_t summaryOffset = buffer.read<int32_t>(false);

  buffer.setPosition(34);
  int32_t verif = buffer.read<int32_t>(false);
  if (verif != 0x80)
  {
    LOG_ERROR("Verification code " << std::hex << verif);
    return core::rcFailure;
  }

  // Encoded data
  rc = archive_.read(buffer, 128, 108);
  if (rc.isFailure())
    return rc;

  int32_t randseed = 1;
  for (int b = 0; b < 108; ++b)
  {
    randseed *= 0x343fd;
    randseed += 0x269ec3;
    buffer.getBuffer()[b] ^= (randseed >> 0x10);
  }

  if (memcmp(buffer.getBuffer(), "AcFssFcAJMB", 11) != 0)
  {
    LOG_ERROR("Decoding failed");
    return core::rcFailure;
  }

//  buffer.setPosition(0x28);
//  int32_t lastSecPid = buffer.read<int32_t>(false);
//  int64_t lastSecPead = buffer.read<int64_t>(false);
//  int64_t repeatedHeader = buffer.read<int64_t>(false);
  buffer.setPosition(0x50);
  /*int32_t secPageMid =*/ buffer.read<int32_t>(false);
  mapOffset_ = buffer.read<uint32_t>(false) + 0x100;
  buffer.setPosition(0x5C);
  infoOffset_ = buffer.read<uint32_t>(false);

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2004::parseInfo()
{
  if (ptrMap_ == NULL)
  {
    LOG_ERROR("No section map to be found");
    return core::rcFailure;
  } else if (ptrInfo_ != NULL) {
    LOG_ERROR("Section info already exists");
    return core::rcFailure;
  }

  const Page* pPage = ptrMap_->findPage(infoOffset_);
  if (pPage == NULL)
  {
    LOG_ERROR("Could not find section info " << infoOffset_);
    return core::rcFailure;
  }

  ptrInfo_.reset(new SectionInfo(archive_, *pPage));
  return ptrInfo_->restore();
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2004::parseMap()
{
  if (ptrMap_ != NULL)
  {
    LOG_ERROR("Section map already exists");
    return core::rcFailure;
  }

  Page page;
  page.offset_ = mapOffset_;
  ptrMap_.reset(new SectionMap(archive_, page));
  return ptrMap_->restore();
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2004::parseObjects(ObjectsParser& parser)
{
  // If info, then map !
  if (ptrInfo_ == NULL)
  {
    LOG_ERROR("No section info to be found");
    return core::rcFailure;
//  } else if (ptrObjects_ != NULL) {
//    LOG_ERROR("Section objects already exists");
//    return core::rcFailure;
  }

  const SectionInfo::Subsection* pObjSec = ptrInfo_->findSubsection(Section::Objects);
  if (pObjSec == NULL)
  {
    LOG_ERROR("Could not find objects' subsection ");
    return core::rcFailure;
  }
  SectionObjects so(archive_, pObjSec->getPages());
LOG_DEBUG("c/e " << pObjSec->isCompressed() << " " << pObjSec->isEncrypted());
  core::ResultCode rc = so.restoreMultiple(*ptrMap_);
  return rc;

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}
