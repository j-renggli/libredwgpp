#pragma once

#include "object.h"

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

class Group : public parserobject::Object
{
  public:
    ~Group() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
