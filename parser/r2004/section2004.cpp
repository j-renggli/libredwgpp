#include "section2004.h"

// TODO
#include "decoder2004_2.h"
#include "sectiondata.h"
#include "sectionpage.h"

namespace libredwg2 {

const int32_t Section2004::s_guardData = 0x4163003b;
const int32_t Section2004::s_guardPage = 0x41630e3b;

////////////////////////////////////////////////////////////////

Section2004::Section2004()//Archive& archive, size_t offset) :
//archive_(archive),
//offset_(offset)
{
}

////////////////////////////////////////////////////////////////

core::ResultCode Section2004::restore(Archive& archive, size_t offset, boost::shared_ptr<Section2004>& ptrSection)
{
  const size_t infoLen = 20;
  core::MemBuffer buffer;
  core::ResultCode rc = archive.read(buffer, offset, infoLen);
  if (rc.isFailure())
    return rc;

  int32_t guard = buffer.read<int32_t>(false);
  int32_t sizeUncomp = buffer.read<int32_t>(false);
  int32_t sizeCompr = buffer.read<int32_t>(false);
  int32_t compressionType = buffer.read<int32_t>(false);
  int32_t checkSum = buffer.read<int32_t>(false);

  LOG_DEBUG("Guard " << guard);
  LOG_DEBUG("sizeUncomp " << sizeUncomp);
  LOG_DEBUG("sizeCompr " << sizeCompr);
  LOG_DEBUG("compressionType " << compressionType);
  LOG_DEBUG("checkSum " << checkSum);

  if (guard == s_guardData) {
    ptrSection.reset(new SectionData);
  } else if (guard == s_guardPage) {
    ptrSection.reset(new SectionPage);
  } else {
    ptrSection.reset();
    LOG_ERROR("Guard is " << std::hex << guard);
    return core::rcFailure;
  }

  rc = archive.read(buffer, offset + infoLen, sizeCompr);
  if (rc.isFailure())
    return rc;

  core::MemBuffer clear;
  clear.resize(sizeUncomp);

  Decoder2004_2 decoder;
  rc = decoder.decode(buffer, clear);
  if (rc.isFailure())
    return rc;

  clear.setPosition(0);

  return ptrSection->restoreData(clear);
}

////////////////////////////////////////////////////////////////

}
