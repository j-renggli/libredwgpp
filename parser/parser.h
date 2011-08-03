#pragma once

#include "../includes.h"
#include "section.h"
#include "version.h"

#include "sections/classes.h"

namespace libredwg2 {

class Archive;
class Decoder;
class DWGBuffer;

class Parser
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  protected:
//    enum Sections
//    {
//      Classes
//    };

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  protected:
    Archive& archive_;

    Version version_;

  private:
    boost::scoped_ptr<ClassesParser> ptrClasses_;
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
    const Version& getVersion() const { return version_; }

    core::ResultCode parse();

  private:
    virtual boost::shared_ptr<Decoder> getDecoder(int compressionMethod) = 0;

    virtual core::ResultCode getSectionBuffer(Section::Type st, DWGBuffer& buffer) = 0;

    virtual core::ResultCode parsePreview();
    virtual core::ResultCode parseClasses();
    virtual core::ResultCode parseFileHeader() = 0;
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
