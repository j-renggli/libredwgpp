#pragma once

#include "object.h"

namespace libredwgpp {

namespace parserobject {

class ShapeFile : public parserobject::Object
{
  public:
    ~ShapeFile() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
