#pragma once

#include "../includes.h"

namespace libredwg2 {

class Archive;
class Decoder;

class Parser
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:
    enum Release {
      R13,
      R14,
      R2000,
      R2004
    };

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  protected:
    Archive& archive_;
//
//    int32_t previewOffset_;
//    int16_t codepage_;
//    int32_t securityFlags_;
//    int32_t summaryOffset_;
//    int32_t sectionMapOffset_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    Parser(Archive& archive);

    virtual ~Parser() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    virtual Release getVersionNumber() const = 0;

    core::ResultCode parse();

  private:
    virtual boost::shared_ptr<Decoder> getDecoder(int compressionMethod) = 0;

    virtual core::ResultCode parseFileHeader() = 0;
    virtual core::ResultCode parsePreview();
    virtual core::ResultCode parseInfo() = 0;
    virtual core::ResultCode parseMap() = 0;
    virtual core::ResultCode parseObjects() = 0;

  private:
//    core::ResultCode uncompress(core::IReadBuffer& compressed, core::MemBuffer& clear, int type);

  public:
    static core::ResultCode create(Archive& archive, boost::shared_ptr<Parser>& ptrLoader);
};

////////////////////////////////////////////////////////////////

}
