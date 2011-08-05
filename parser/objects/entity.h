#pragma once

#include "../object.h"

namespace libredwg2 {

namespace parserobject {

class Entity : public Object
{
  public:
    ~Entity() {}

  public:
    virtual core::ResultCode restore(Schema& schema, DWGBuffer& buffer, const Version& version) const;

  private:
    virtual core::ResultCode restoreFull(Schema& schema, DWGBuffer& buffer, const Version& version) const = 0;
};

////////////////////////////////////////////////////////////////

}

}
