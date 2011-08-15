#pragma once

#include "../object.h"

namespace libredwgpp {

class Colour;

namespace parserobject {

class Entity : public libredwgpp::Object
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
