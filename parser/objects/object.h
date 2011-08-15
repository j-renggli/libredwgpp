#pragma once

#include "../object.h"

namespace libredwgpp {

namespace parserobject {

class Object : public libredwgpp::Object
{
  public:
    ~Object() {}

  public:
    virtual core::ResultCode restore(ISchema& schema, DWGBuffer& buffer, const Version& version) const;

  private:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Version& version) const = 0;
};

////////////////////////////////////////////////////////////////

}

}
