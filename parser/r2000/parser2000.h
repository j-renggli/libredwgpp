#pragma once

#include "../page.h"
#include "../parser.h"

namespace libredwg2 {

//class SectionInfo;
//class SectionMap;

class Parser2000 : public Parser
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  private:
    enum Type {
      HEADER = 0,
      CLASS = 1,
      OBJECT = 2,
      SPECIAL = 3,
      MEASUREMENT = 4,
      OTHER = 5
    };

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    /// Map to all sections
    std::vector<Page> vPages_;

    /// Info about each part of the archive
//    boost::scoped_ptr<SectionInfo> ptrInfo_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    Parser2000(Archive& archive);

    virtual ~Parser2000();

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    virtual Parser::Release getVersionNumber() const { return Parser::R2000; }

  private:
    virtual boost::shared_ptr<Decoder> getDecoder(int compressionMethod);

    virtual core::ResultCode parseFileHeader();
    virtual core::ResultCode parseInfo();
    virtual core::ResultCode parseMap();
    virtual core::ResultCode parseObjects();

};

////////////////////////////////////////////////////////////////

}
