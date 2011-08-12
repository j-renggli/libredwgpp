#pragma once

#include "../object.h"

namespace libredwg2 {

class Colour;

namespace parserobject {

class Entity : public libredwg2::Object
{
  public:
    ~Entity() {}

  public:
    virtual core::ResultCode restore(Schema& schema, DWGBuffer& buffer, const Version& version) const;

  private:
    virtual core::ResultCode restoreFull(Schema& schema, DWGBuffer& buffer, const Colour& colour, const Version& version) const = 0;
};

////////////////////////////////////////////////////////////////

}

}
