#pragma once

#include "../includes.h"

namespace libredwgpp {

class Class
{
  ////////////////////////////////////////////////////////////////
  // Definitions
  ////////////////////////////////////////////////////////////////
  public:

  ////////////////////////////////////////////////////////////////
  // Members
  ////////////////////////////////////////////////////////////////
  private:
    size_t id_;
    uint16_t flags_;
    UnicodeString strAppName_;
    UnicodeString strCppName_;
    UnicodeString strDxfName_;
    bool wasZombie_;
    size_t itemClassID_;

  ////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  ////////////////////////////////////////////////////////////////
  public:
    Class(size_t id, uint16_t flags, const UnicodeString& strAppName, const UnicodeString& strCppName,
          const UnicodeString& strDxfName, bool wasZombie, size_t itemClassID);

    virtual ~Class() {}

  ////////////////////////////////////////////////////////////////
  // Functions
  ////////////////////////////////////////////////////////////////
  public:
    const UnicodeString& getAppName() const { return strAppName_; }
    const UnicodeString& getCppName() const { return strCppName_; }
    const UnicodeString& getDxfName() const { return strDxfName_; }

  private:
//    virtual core::ResultCode restore(DWGBuffer& buffer);
};

////////////////////////////////////////////////////////////////

}
