#pragma once

#include "entity.h"

namespace libredwg2 {

namespace parserobject {

class Vertex3D : public Entity
{
  public:
    ~Vertex3D() {}

  public:
    virtual core::ResultCode restoreFull(Schema& schema, DWGBuffer& buffer, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
