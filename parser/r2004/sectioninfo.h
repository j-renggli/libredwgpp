#pragma once

#include "../page.h"
#include "section2004.h"

namespace libredwgpp {

class SectionInfo : public Section2004
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:
    class Subsection
    {
//      public:
//        enum Type {
//          HEADER,
//          AUXHEADER,
//          CLASSES,
//          HANDLES,
//          TEMPLATE,
//          OBJFREESPACE,
//          OBJECTS,
//          REVHISTORY,
//          SUMMARY,
//          PREVIEW,
//          APPINFO,
//          APPINFOHISTORY,
//          FILEDEPS,
//    //      SECURITY,
//
//          UNKNOWN
//        };

      private:
        /// An id for the subsection
        int32_t id_;

        /// Maximum size of each page
        int32_t pageSize_;

//        /// The uncompressed size of sections put together
        int64_t size_;

        bool isCompressed_;
        bool isEncrypted_;
//        std::string strName_;
        std::vector<Page> vPages_;

      public:
        Subsection(int32_t id, int64_t size, bool isCompressed, bool isEncrypted, int32_t pageSize, const std::vector<Page>& vPages);

      public:
        int32_t getID() const { return id_; }

        const std::vector<Page>& getPages() const { return vPages_; }

        int64_t getPageSize() const { return pageSize_; }

        bool isCompressed() const { return isCompressed_; }

        bool isEncrypted() const { return isEncrypted_; }
    };

    typedef std::map<Section::Type, Subsection> SubsectionMap;

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    SubsectionMap mSubsections_;

    static const int32_t s_guard;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    SectionInfo(Archive& archive, const Page& single);

    virtual ~SectionInfo() {}

  ////////////////////////////////////////////////////////////////
  // Operators
  ////////////////////////////////////////////////////////////////
  private:

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    const Subsection* findSubsection(Section::Type type) const;

  private:
    virtual int32_t getGuard() const { return s_guard; }

    virtual core::ResultCode restoreData(DWGBuffer& buffer);
};

////////////////////////////////////////////////////////////////

}
