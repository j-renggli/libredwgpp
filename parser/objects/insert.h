#pragma once

#include "entity.h"

namespace libredwgpp {

namespace parserobject {

class Insert : public Entity
{
  public:
    ~Insert() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
