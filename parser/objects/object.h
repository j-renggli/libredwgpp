#pragma once

#include "../object.h"

namespace libredwgpp {

namespace parserobject {

class Object : public libredwgpp::Object
{
  public:
    ~Object() {}

  public:
    virtual core::ResultCode restore(Schema& schema, DWGBuffer& buffer, const Version& version) const;

  private:
    virtual core::ResultCode restoreFull(Schema& schema, DWGBuffer& buffer, const Version& version) const = 0;
};

////////////////////////////////////////////////////////////////

}

}
