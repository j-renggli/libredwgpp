#pragma once

#include "entity.h"

namespace libredwgpp {

namespace parserobject {

class Vertex3D : public Entity
{
  public:
    ~Vertex3D() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
