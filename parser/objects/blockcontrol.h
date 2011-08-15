#pragma once

#include "object.h"

namespace libredwgpp {

namespace parserobject {

class BlockControl : public parserobject::Object
{
  public:
    ~BlockControl() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
