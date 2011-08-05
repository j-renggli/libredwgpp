#pragma once

#include <includes.h>

#include "dwgbuffer.h"

namespace libredwg2 {

class Schema;
class Version;

class Object
{
  public:
    ~Object() {}

  public:
    virtual core::ResultCode restore(Schema& schema, DWGBuffer& buffer, const Version& version) const = 0;
};

////////////////////////////////////////////////////////////////

}
