#pragma once

#include "object.h"

namespace libredwg2 {

namespace parserobject {

class ShapeFile : public parserobject::Object
{
  public:
    ~ShapeFile() {}

  public:
    virtual core::ResultCode restoreFull(Schema& schema, DWGBuffer& buffer, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
