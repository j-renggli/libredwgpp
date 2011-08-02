#include "dwgbuffer.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

DWGBuffer::DWGBuffer() :
offset_(0),
last_(0)
{
}

////////////////////////////////////////////////////////////////

DWGBuffer::DWGBuffer(const core::IReadBuffer& buffer) :
buffer_(buffer),
offset_(0),
last_(0)
{
  buffer_.setPosition(0);
}

////////////////////////////////////////////////////////////////

size_t DWGBuffer::getPosition() const {
  return buffer_.getPosition();
}

////////////////////////////////////////////////////////////////

bool DWGBuffer::hasMore() const {
  return buffer_.getPosition() < buffer_.getSize();
}

////////////////////////////////////////////////////////////////

bool DWGBuffer::readBit()
{
  if (offset_ == 0)
  {
    buffer_.readValue(last_, false);
    offset_ = 1;
    return (last_ & 0x80) != 0;
  } else {
    bool on = (last_ >> (7 - offset_)) & 0x01;
    offset_ = (offset_ + 1) % 8;
    return on;
  }
}

////////////////////////////////////////////////////////////////

uint8_t DWGBuffer::readBit2()
{
  core::Buffer result;

  if (offset_ == 0)
  {
    buffer_.readValue(last_, false);
    result = last_ >> 6;
    offset_ = 2;
  } else if (offset_ < 7) {
    result = (last_ >> (6 - offset_)) & 0x3;
    offset_ = (offset_ + 2) % 8;
  } else {
    result = (last_ & 0x01) << 1;
    buffer_.readValue(last_, false);
    result |= (last_ & 0x80) >> 7;
    offset_ = 1;
  }

  return result;
}

////////////////////////////////////////////////////////////////

uint16_t DWGBuffer::readBit16()
{
  const uint8_t b2 = readBit2();
  switch (b2)
  {
    case 0:
      return readRaw16();
    case 1:
      return readRaw8();
    case 2:
      return 0;
    case 3:
      return 256;
    default:
    {
      LOG_ERROR("Unexpected value " << std::hex << b2);
      throw std::out_of_range("2-bit code (16)");
    }
  }
}

////////////////////////////////////////////////////////////////

uint32_t DWGBuffer::readBit32()
{
  const uint8_t b2 = readBit2();
  switch (b2)
  {
    case 0:
      return readRaw32();
    case 1:
      return readRaw8();
    case 2:
      return 0;
    default:
    {
      LOG_ERROR("Unexpected value " << std::hex << b2);
      throw std::out_of_range("2-bit code (32)");
    }
  }
}

////////////////////////////////////////////////////////////////

double DWGBuffer::readBitDouble()
{
  const uint8_t b2 = readBit2();
  switch (b2)
  {
    case 0:
      return readRawDouble();
    case 1:
      return 1.;
    case 2:
      return 0.;
    default:
    {
      LOG_ERROR("Unexpected value " << std::hex << b2);
      throw std::out_of_range("2-bit code (double)");
    }
  }
}

////////////////////////////////////////////////////////////////

Colour DWGBuffer::readColour()
{
  Colour col;
  col.index_ = readBit16();
  return col;
}

////////////////////////////////////////////////////////////////

Colour DWGBuffer::readColourAdvanced()
{
//  Colour col;
//  col.index_ = readBit16();
//  col.rgb_ = readBit32();
//  uint8_t c = readRaw8();
//  if (c & 0x01)
//    col.strName_ = readText();
//  else if (c & 0x02)
//    col.strBookName_ = readText();
//  return col;
}

////////////////////////////////////////////////////////////////

Handle DWGBuffer::readHandle()
{
  Handle handle;
  handle.code_ = readRaw8();
  uint8_t size = handle.code_ & 0x0F;
  handle.code_ = (handle.code_ & 0xF0) >> 4;
  if (size > 4)
  {
    throw std::overflow_error("Handle size");
  }

  handle.value_ = 0;
  uint8_t* pValue = (uint8_t*)(&handle.value_);
  for (int i = size -1; i >= 0; --i)
    pValue[i] = readRaw8();

  return handle;
}

////////////////////////////////////////////////////////////////

int32_t DWGBuffer::readModularChar()
{
//  bool isNegative = false;
  uint32_t byte;
  int32_t result = 0;
//  int j = 0;
//  for (int i = 3; i >= 0; --i)
  for (int j = 0; j < 25; j += 7)
  {
    byte = readRaw8();
    if (byte & 0x80) {
      byte &= 0x7F;
    } else {
      result |= ((byte & 0xbf) << j);

      if (byte & 0x40)
        return -result;

      return result;
    }

    result |= (byte << j);
//    j += 7;
  }

  // Should not arrive here
  throw std::overflow_error("Modular char");
}

////////////////////////////////////////////////////////////////

int32_t DWGBuffer::readModularShort()
{
//  bool isNegative = false;
  uint32_t val;
  int32_t result = 0;
  for (int j = 0; j < 25; j += 15)
  {
    val = readRaw16();
    if (val & 0x8000) {
      val &= 0x7FFF;
    } else {
      result |= ((val & 0xBFFF) << j);

      if (val & 0x4000)
        return -result;

      return result;
    }

    result |= (val << j);
  }

  // Should not arrive here
  throw std::overflow_error("Modular short");
}

////////////////////////////////////////////////////////////////

uint8_t DWGBuffer::readRaw8()
{
  core::Buffer temp = last_;
  buffer_.readValue(last_, false);

  if (offset_ > 0)
  {
    return (temp << offset_) | (last_ >> (8 - offset_));
  } else {
    return last_;
  }
}

////////////////////////////////////////////////////////////////

uint16_t DWGBuffer::readRaw16()
{
  uint16_t byte1 = readRaw8();
  uint16_t byte2 = readRaw8();
  return (byte2 << 8) | byte1;
}

////////////////////////////////////////////////////////////////

uint32_t DWGBuffer::readRaw32()
{
  uint32_t byte1 = readRaw16();
  uint32_t byte2 = readRaw16();
  return (byte2 << 16) | byte1;
}

////////////////////////////////////////////////////////////////

double DWGBuffer::readRawDouble()
{
  double value;
  uint8_t* pValue = (uint8_t*)&value;
LOG_DEBUG(offset_);
  for (int i = 0; i < 8; ++i)
    pValue[i] = readRaw8();

  return value;
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readText(std::string& strText)
{
  uint16_t size = readBit16();
  strText.resize(size);

  for (uint16_t i = 0; i < size; ++i)
  {
    char c = readRaw8();
    if (c == 0) {
      strText.resize(i);
      return;
    } else if (!isprint(c)) {
      strText[i] = '~';
    } else {
      strText[i] = c;
    }
  }

  strText.append('\0');
}

////////////////////////////////////////////////////////////////

void DWGBuffer::setPosition(size_t pos)
{
  last_ = 0;
  offset_ = 0;
  buffer_.setPosition(pos);
}

////////////////////////////////////////////////////////////////

void DWGBuffer::skipBits()
{
  if (offset_ == 0)
    return;

  offset_ = 0;
  last_ = 0;
}

////////////////////////////////////////////////////////////////

void DWGBuffer::skipBytes(size_t length)
{
  buffer_.setPosition(buffer_.getPosition() + length - 1);
  buffer_.readValue(last_, false);
}

////////////////////////////////////////////////////////////////

}
