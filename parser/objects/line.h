#pragma once

#include "entity.h"

namespace libredwgpp {

namespace parserobject {

class Line : public Entity
{
  public:
    ~Line() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
