#pragma once

#include "entity.h"

namespace libredwg2 {

namespace parserobject {

class Line : public Entity
{
  public:
    ~Line() {}

  public:
    virtual core::ResultCode restoreFull(Schema& schema, DWGBuffer& buffer, const Colour& colour, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
