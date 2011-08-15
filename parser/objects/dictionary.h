#pragma once

#include "object.h"

namespace libredwgpp {

namespace parserobject {

class Dictionary : public parserobject::Object
{
  public:
    ~Dictionary() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
