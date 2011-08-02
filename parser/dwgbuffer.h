#pragma once

#include <core/includes.h>

#include "colour.h"
#include "handle.h"

namespace libredwg2 {

class DWGBuffer
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    /// The buffer to read from
    core::MemBuffer buffer_;

    /// The bit offset if present
    int offset_;

    /// The last byte read (cf. bit offset)
    core::Buffer last_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    DWGBuffer();
    DWGBuffer(const core::IReadBuffer& buffer);

    virtual ~DWGBuffer() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    core::IReadWriteBuffer& getBuffer() { return buffer_; }

    size_t getPosition() const;
    bool hasMore() const;

    /// "Bit" read
    bool readBit();
    uint8_t readBit2();
    uint16_t readBit16();
    uint32_t readBit32();
    double readBitDouble();

    /// "Colour" read
    Colour readColour();
    Colour readColourAdvanced();

    /// Handle references
    Handle readHandle();

    /// Modular integers
    int32_t readModularChar();
    int32_t readModularShort();

    /// "Raw" read
    uint8_t readRaw8();
    uint16_t readRaw16();
    uint32_t readRaw32();
    double readRawDouble();

    /// "Text" read
    void readText(std::string& strText); // 2004 and earlier

    /// Set the position in terms of bytes (=> offset reset to 0)
    void setPosition(size_t pos);

    /// Skip as many bits as necessary to have offset = 0 (do nothing if already there)
    void skipBits();

    /// Skip n bytes (offset unchanged)
    void skipBytes(size_t length);
};

////////////////////////////////////////////////////////////////

}
