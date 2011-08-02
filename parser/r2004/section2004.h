#pragma once

#include "../page.h"

#include <file/archive.h>
#include <parser/section.h>

namespace libredwg2 {

class DWGBuffer;
class SectionMap;

class Section2004 : public Section
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:
    typedef std::vector<Page> PageVector;

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  protected:
    /// The archive to read from
    Archive& archive_;

    /// The section identifier

  private:
    /// Multiple pages to read
    PageVector vPages_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    Section2004(Archive& archive, const Page& single);

    Section2004(Archive& archive, const std::vector<Page>& multiple);

    virtual ~Section2004() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    /// Restore a section chosing the correct type
//    static core::ResultCode restore(Archive& archive, size_t offset, boost::shared_ptr<Section2004>& ptrSection);

    /// Restore for basic data (map & info)
    virtual core::ResultCode restore();

    /// Restore from multiple sections
    virtual core::ResultCode restoreMultiple(const SectionMap& map);

  private:
    virtual int32_t getGuard() const = 0;

    virtual core::ResultCode restoreData(DWGBuffer& buffer) = 0;
};

////////////////////////////////////////////////////////////////

}
