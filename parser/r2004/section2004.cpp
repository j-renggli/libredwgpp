#include "section2004.h"

// TODO
#include "decoder2004_2.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Section2004::Section2004(Archive& archive, size_t offset) :
archive_(archive),
offset_(offset)
{
}

////////////////////////////////////////////////////////////////

//  class DataSection {
//    public:
//      int id_;
//      size_t address_;
//      size_t size_;
//  };

core::ResultCode Section2004::restore()
{
  const size_t infoLen = 20;
  core::MemBuffer buffer;
  core::ResultCode rc = archive_.read(buffer, offset_, infoLen);
  if (rc.isFailure())
    return rc;

  int32_t guard = buffer.read<int32_t>(false);
  if (guard != getGuard())
  {
    LOG_ERROR("Expected " << getGuard() << ", got " << guard);
    return core::rcFailure;
  }

  int32_t sizeUncomp = buffer.read<int32_t>(false);
  int32_t sizeCompr = buffer.read<int32_t>(false);
  int32_t compressionType = buffer.read<int32_t>(false);
  int32_t checkSum = buffer.read<int32_t>(false);

  LOG_DEBUG("sizeUncomp " << sizeUncomp);
  LOG_DEBUG("sizeCompr " << sizeCompr);
  LOG_DEBUG("compressionType " << compressionType);
  LOG_DEBUG("checkSum " << checkSum);

  rc = archive_.read(buffer, offset_ + infoLen, sizeCompr);
  if (rc.isFailure())
    return rc;

  core::MemBuffer clear;
  clear.resize(sizeUncomp);

  Decoder2004_2 decoder;
  rc = decoder.decode(buffer, clear);
  if (rc.isFailure())
    return rc;

  clear.setPosition(0);

  return restoreData(clear);
}

////////////////////////////////////////////////////////////////

}
