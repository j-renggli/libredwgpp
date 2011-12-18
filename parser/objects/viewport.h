#pragma once

#include "object.h"

namespace libredwgpp {

namespace parserobject {

class Viewport : public parserobject::Object
{
  public:
    ~Viewport() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
