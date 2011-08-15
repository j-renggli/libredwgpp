#pragma once

#include "object.h"

namespace libredwgpp {

namespace parserobject {

class Layer : public parserobject::Object
{
  public:
    ~Layer() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
