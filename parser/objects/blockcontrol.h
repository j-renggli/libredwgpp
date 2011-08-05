#pragma once

#include "object.h"

namespace libredwg2 {

namespace parserobject {

class BlockControl : public parserobject::Object
{
  public:
    ~BlockControl() {}

  public:
    virtual core::ResultCode restoreFull(Schema& schema, DWGBuffer& buffer, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
