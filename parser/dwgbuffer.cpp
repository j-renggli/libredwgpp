#include "dwgbuffer.h"

#include "version.h"

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

UnicodeString DWGBuffer::readASCII()
{
  size_t size = readBit16();
  UnicodeString strText(size, '\0', size);

  for (size_t i = 0; i < size; ++i)
  {
    char c = readRaw8();
    if (c == 0) {
//      strText.resize(i);
      return strText;
//    } else if (!isprint(c)) {
//      strText.setCharAt(i, '~'); // ?
    } else {
      strText.setCharAt(i, c);
    }
  }

  strText.append('\0');
  return strText;
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

uint8_t DWGBuffer::readBit3()
{
  core::Buffer result = 0;

  for (int i = 0; i < 3; ++i)
  {
    result <<= 1;
    bool isOne = readBit();
    if (isOne)
      ++result;
    else
      break;
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

uint64_t DWGBuffer::readBit64()
{
  const uint8_t b3 = readBit3();

  uint64_t result = 0;
  int shift = 0;
  for (int i = 0; i < b3; ++i)
  {
    uint64_t a = readRaw8();
    result |= (a << shift);
    shift += 8;
  }

  return result;
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

void DWGBuffer::readBitDouble(double& valueWithDefault)
{
  const uint8_t b2 = readBit2();
  switch (b2)
  {
    case 0:
      return;
    case 1:
    LOG_DEBUG("Double 4");
    exit(0);
      return;
    case 2:
    LOG_DEBUG("Double 6");
    exit(0);
      return;
    default:
    {
      valueWithDefault = readRawDouble();
      return;
    }
  }
}

////////////////////////////////////////////////////////////////

void DWGBuffer::readBitExtrusion(const Version& version, double& x, double& y, double& z)
{
  if (version.isAtLeast(Version::R2000))
  {
    if (readBit())
    {
      x = 0.;
      y = 0.;
      z = 1.;
      return;
    }
  }

  x = readBitDouble();
  y = readBitDouble();
  z = readBitDouble();
}

////////////////////////////////////////////////////////////////

Colour DWGBuffer::readColour(const Version& version)
{
  Colour col;

  if (version.isAtLeast(Version::R2004))
  {
    col.index_ = readBit16();
    col.rgb_ = readBit32();
    uint8_t c = readRaw8();
    if (c & 0x01)
      col.strName_ = readText(version);
    else if (c & 0x02)
      col.strBookName_ = readText(version);
  } else {
    col.index_ = readBit16();
  }
  return col;
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
  for (int i = size - 1; i >= 0; --i)
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

  for (int i = 0; i < 8; ++i)
    pValue[i] = readRaw8();

  return value;
}

////////////////////////////////////////////////////////////////

UnicodeString DWGBuffer::readText(const Version& version)
{
  if (version.isAtLeast(Version::R2007))
    return readUTF16();
  else
    return readASCII();
}

////////////////////////////////////////////////////////////////

UnicodeString DWGBuffer::readUTF16()
{
  size_t size = readBit16();
  UnicodeString strText(size, '\0', size);

  for (size_t i = 0; i < size; ++i)
  {
    uint16_t c = readRaw16();
    if (c == 0) {
//      strText.resize(i);
      return strText;
//    } else if (!isprint(c)) {
//      strText.setCharAt(i, '~'); // ?
    } else {
      strText.setCharAt(i, c);
    }
  }

  strText.append('\0');
  return strText;
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
