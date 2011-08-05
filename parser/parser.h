#pragma once

#include "../includes.h"
#include "section.h"
#include "version.h"

#include "sections/classes.h"
#include "sections/objects.h"

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

    boost::shared_ptr<Schema> ptrSchema_;

    boost::scoped_ptr<ClassesParser> ptrClasses_;

  private:
    boost::scoped_ptr<ObjectsParser> ptrObjects_;

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
    const boost::shared_ptr<Schema>& getSchema() const { return ptrSchema_; }

    const Version& getVersion() const { return version_; }

    core::ResultCode parse();

  private:
    virtual boost::shared_ptr<Decoder> getDecoder(int compressionMethod) = 0;

    virtual core::ResultCode getSectionBuffer(Section::Type st, DWGBuffer& buffer) = 0;

    virtual core::ResultCode parsePreview();
    virtual core::ResultCode parseClasses();

    virtual core::ResultCode parseObjects(ObjectsParser& parser) = 0;

    virtual core::ResultCode parseFileHeader() = 0;
    virtual core::ResultCode parseInfo() = 0;
    virtual core::ResultCode parseMap() = 0;

  private:
//    core::ResultCode uncompress(core::IReadBuffer& compressed, core::MemBuffer& clear, int type);

  public:
    static core::ResultCode create(Archive& archive, boost::shared_ptr<Parser>& ptrLoader);
};

////////////////////////////////////////////////////////////////

}
