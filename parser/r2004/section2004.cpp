#include "section2004.h"

#include "sectionmap.h"
#include "../dwgbuffer.h"

// TODO
#include "decoder2004_2.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Section2004::Section2004(Archive& archive, const Page& single) :
archive_(archive)
{
  vPages_.push_back(single);
}

////////////////////////////////////////////////////////////////

Section2004::Section2004(Archive& archive, const std::vector<Page>& multiple) :
archive_(archive),
vPages_(multiple)
{
}

////////////////////////////////////////////////////////////////

core::ResultCode Section2004::restore()
{
  ASSERT(vPages_.size() == 1);

  const size_t infoLen = 20;
  core::MemBuffer buffer;
  core::ResultCode rc = archive_.read(buffer, vPages_[0].offset_, infoLen);
  if (rc.isFailure())
    return rc;

  int32_t guard = buffer.read<int32_t>(false);
  int32_t sizeUncomp = buffer.read<int32_t>(false);
  int32_t sizeCompr = buffer.read<int32_t>(false);
  // TODO: use compression type !!!
  int32_t compressionType = buffer.read<int32_t>(false);
//  int32_t checkSum = buffer.read<int32_t>(false);

//  LOG_DEBUG("Guard " << guard);
//  LOG_DEBUG("sizeUncomp " << sizeUncomp);
//  LOG_DEBUG("sizeCompr " << sizeCompr);
//  LOG_DEBUG("compressionType " << compressionType);
//  LOG_DEBUG("checkSum " << checkSum);

  if (guard != getGuard()) {
    LOG_ERROR("Guard is " << std::hex << guard << " expected " << getGuard());
    return core::rcFailure;
  }

  rc = archive_.read(buffer, vPages_[0].offset_ + infoLen, sizeCompr);
  if (rc.isFailure())
    return rc;

  core::MemBuffer clear;
  clear.reserve(sizeUncomp);

  Decoder2004_2 decoder;
  DWGBuffer in(buffer);
  rc = decoder.decode(in, clear);
  if (rc.isFailure())
    return rc;

  DWGBuffer data(clear);
  return restoreData(data);
}

////////////////////////////////////////////////////////////////

core::ResultCode Section2004::restoreMultiple(const SectionMap& map)
{
  if (vPages_.empty())
  {
    LOG_ERROR("No pages to restore!");
    return core::rcFailure;
  }
LOG_DEBUG(vPages_[0].size_);
  core::MemBuffer raw, clear;
  clear.reserve(/*pObjSec->getPageSize()*/ 0x7400 * vPages_.size());

  for (PageVector::const_iterator it = vPages_.begin(); it != vPages_.end(); ++it)
  {
    const uint32_t offset = map.findPage(it->id_)->offset_;
LOG_DEBUG(offset << " vs " << it->offset_);
    archive_.read(raw, offset, 0x20);
    const uint32_t mask = 0x4164536b ^ offset;
    uint32_t* pBuffer = (uint32_t*)raw.getBuffer();

    for (int i = 0; i < 8; ++i)
      pBuffer[i] ^= mask;

    uint32_t guard = raw.read<uint32_t>(false);
    uint32_t sectionID = raw.read<uint32_t>(false);
    uint32_t encodedSize = raw.read<uint32_t>(false);
    uint32_t decodedSize = raw.read<uint32_t>(false);
    uint32_t startOffset = raw.read<uint32_t>(false); // Start offset in the decompressed buffer
    uint32_t unknown = raw.read<uint32_t>(false);
    uint32_t checksum_1 = raw.read<uint32_t>(false);
    uint32_t checksum_2 = raw.read<uint32_t>(false);

    LOG_DEBUG("guard " << guard);
    LOG_DEBUG("sectionID " << sectionID);
    LOG_DEBUG("encodedSize " << encodedSize);
    LOG_DEBUG("decodedSize " << decodedSize);
    LOG_DEBUG(">>" << startOffset);
//    LOG_DEBUG("CRC " << checksum_1);
//    LOG_DEBUG("CRC " << checksum_2);

    if (guard != getGuard()) {
      LOG_ERROR("Guard is " << std::hex << guard << " expected " << getGuard());
      return core::rcFailure;
    }

    archive_.read(raw, offset + 0x20, encodedSize);
    Decoder2004_2 decoder;
    DWGBuffer in(raw);
    core::ResultCode rc = decoder.decode(in, clear);
//    if (rc.isFailure())
////      return rc;
//break;
  }

  DWGBuffer data(clear);
  return restoreData(data);
}

////////////////////////////////////////////////////////////////

}
