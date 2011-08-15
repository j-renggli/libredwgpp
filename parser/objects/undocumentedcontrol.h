#pragma once

#include "object.h"

namespace libredwgpp {

namespace parserobject {

class UndocumentedControl : public parserobject::Object
{
  private:
    UnicodeString strName_;

  public:
    UndocumentedControl(const UnicodeString& strName) : strName_(strName) {}

    ~UndocumentedControl() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
