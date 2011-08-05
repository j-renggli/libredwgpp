#pragma once

#include "../parser.h"

namespace libredwg2 {

class SectionInfo;
class SectionMap;

class Parser2004 : public Parser
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    /// Map to all sections
    size_t mapOffset_;
    boost::scoped_ptr<SectionMap> ptrMap_;

    /// Info about each part of the archive
    size_t infoOffset_;
    boost::scoped_ptr<SectionInfo> ptrInfo_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    Parser2004(Archive& archive);

    virtual ~Parser2004();

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
//    virtual Parser::Release getVersionNumber() const { return Parser::R2004; }

  private:
    virtual boost::shared_ptr<Decoder> getDecoder(int compressionMethod);

    virtual core::ResultCode getSectionBuffer(Section::Type st, DWGBuffer& buffer);
//    virtual core::ResultCode parse();

//    virtual core::ResultCode parseClasses();
    virtual core::ResultCode parseFileHeader();
    virtual core::ResultCode parseInfo();
    virtual core::ResultCode parseMap();
    virtual core::ResultCode parseObjects(ObjectsParser& parser);

};

////////////////////////////////////////////////////////////////

}
