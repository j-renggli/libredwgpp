#include "decoder2004_2.h"

#include "../dwgbuffer.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

core::ResultCode Decoder2004_2::decode(core::IReadBuffer& raw, core::IWriteBuffer& out)
{
  DWGBuffer in(raw);

  uint8_t opcode = 0;
  uint32_t litlen = readLiteralLength(in, opcode);

  for (uint32_t i = 0; i < litlen; ++i)
    out.write(in.readRaw8());
//LOG_DEBUG(raw.getSize());
//  opcode = 0x00;
  while (in.hasMore())
  {
    if (opcode == 0x00)
    {
      opcode = in.readRaw8();
    }

//    LOG_DEBUG(std::hex << (uint16_t)opcode);
    uint32_t bytelen = 0;
    int32_t byteoffset = 0;

    if (opcode == 0x11) {
      break; // Terminates the input stream, everything is ok!
    } else if (opcode >= 0x40) {
      bytelen = ((opcode & 0xF0) >> 4) - 1;
      uint32_t opnew = in.readRaw8();
      byteoffset = (opnew << 2) | uint32_t((opcode & 0x0C) >> 2);

      if (opcode & 0x03)
      {
        litlen = (opcode & 0x03);
        opcode = 0x00;
      } else {
        litlen = readLiteralLength(in, opcode);
      }
    } else {
      if (opcode >= 0x21 && opcode <= 0x3F) {
        bytelen = opcode - 0x1E;
        byteoffset = readOffset2b(in, litlen);
      } else if (opcode == 0x20) {
        bytelen = readOffsetLong(in) + 0x21;
        byteoffset = readOffset2b(in, litlen);
      } else if (opcode >= 0x12 && opcode <= 0x1F) {
        bytelen = (opcode & 0x0F) + 2;
        byteoffset = readOffset2b(in, litlen) + 0x3FFF;
      } else if (opcode == 0x10) {
        bytelen = readOffsetLong(in) + 9;
        byteoffset = readOffset2b(in, litlen) + 0x3FFF;
      } else {
        LOG_ERROR("Decompressing opcode " << std::hex << opcode << " after decompressing " << out.getSize() << " bytes");
        return core::rcFailure;
      }

      if (litlen != 0)
        opcode = 0x00;
      else
        litlen = readLiteralLength(in, opcode);
    }

    // Copy compressed data
    uint32_t current = out.getPosition();
//    LOG_DEBUG(current << " " << (int)bytelen << " " << byteoffset << " " << out.getSize());
    if (byteoffset != 0 && (int)current - byteoffset - 1 < 0)
    {
      LOG_DEBUG("Wrong offset " << byteoffset << " after decompressing " << current << " bytes");
      return core::rcFailure;
    }
    for (uint32_t i = 0; i < bytelen; ++i)
      out.write<core::Buffer>(out.getBuffer()[current - byteoffset + i - 1]);

//LOG_DEBUG("b");
    // Copy data directly
    for (uint32_t i = 0; i < litlen; ++i)
      out.write(in.readRaw8());
  }

//LOG_DEBUG("x");
  LOG_DEBUG(out.getSize() << " bytes written");

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

uint32_t Decoder2004_2::readLiteralLength(DWGBuffer& in, uint8_t& opcode)
{
  uint32_t total = 0;
  uint8_t byte = in.readRaw8();

  opcode = 0x00;

  if (byte == 0) {
    total = 0x0F;
    while ((byte = in.readRaw8()) == 0x00)
      total += 0xFF;

    return total + byte + 3;
  } else if (byte & 0xF0) {
    opcode = byte;
  } else if (byte >= 0x01 && byte <= 0x0F) {
    return byte + 3;
  }

  return 0;
}

////////////////////////////////////////////////////////////////

uint32_t Decoder2004_2::readOffset2b(DWGBuffer& in, uint32_t& litlen)
{
  uint32_t first = in.readRaw8();
  uint32_t second = in.readRaw8();

//  LOG_DEBUG(std::hex << (uint16_t)first << " " << (uint16_t)second);

  litlen = first & 0x03;
  return (first >> 2) | (second << 6);
}

////////////////////////////////////////////////////////////////

uint32_t Decoder2004_2::readOffsetLong(DWGBuffer& in)
{
  uint32_t total = 0;
  int8_t byte = in.readRaw8();
  if (byte == 0)
  {
    total = 0xFF;
    while ((byte = in.readRaw8()) == 0x00)
      total += 0xFF;
  }

  return total + byte;
}

////////////////////////////////////////////////////////////////

}
