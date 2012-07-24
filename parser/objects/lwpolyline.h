#pragma once

#include "entity.h"

namespace libredwgpp {

namespace parserobject {

// LWPOLYLINE
class PolyLine : public Entity
{
  public:
    ~PolyLine() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
