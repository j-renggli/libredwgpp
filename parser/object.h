#pragma once

#include "../includes.h"

#include "dwgbuffer.h"

namespace libredwgpp {

class ISchema;

class Handle;
class Version;

class Object
{
  public:
    ~Object() {}

  public:
    virtual core::ResultCode restore(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const = 0;
};

////////////////////////////////////////////////////////////////

}
