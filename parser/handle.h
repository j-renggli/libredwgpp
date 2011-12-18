#pragma once

#include "../includes.h"

namespace libredwgpp {

class Handle
{
  public:
    Handle(uint8_t code = -1, uint32_t value = -1);

  public:
    size_t getCode() const { return code_; }

    size_t getValue() const { return value_; }

  private:
    uint8_t code_;
    uint32_t value_;

};

////////////////////////////////////////////////////////////////

}
