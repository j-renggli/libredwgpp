#include "dwgbuffer.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

DWGBuffer::DWGBuffer(const core::MemBuffer& buffer) :
buffer_(buffer),
offset_(0),
last_(0)
{
  buffer_.setPosition(0);
}

////////////////////////////////////////////////////////////////

bool DWGBuffer::hasMore() const {
  return buffer_.getPosition() < buffer_.getSize();
}

////////////////////////////////////////////////////////////////

uint8_t DWGBuffer::readRC()
{
  core::Buffer byte, next;
  buffer_.readValue(next);

  if (offset_ > 0)
  {
    byte = (last_ << offset_) | (next >> (8 - offset_));
  } else {
    byte = next;
  }

  last_ = next;
  return byte;
}

////////////////////////////////////////////////////////////////

}
