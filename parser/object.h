#pragma once

#include "../includes.h"

#include "dwgbuffer.h"

namespace libredwgpp {

class ISchema;

class Version;

class Object
{
  public:
    ~Object() {}

  public:
    virtual core::ResultCode restore(ISchema& schema, DWGBuffer& buffer, const Version& version) const = 0;
};

////////////////////////////////////////////////////////////////

}
