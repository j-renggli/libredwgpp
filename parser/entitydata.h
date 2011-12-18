#pragma once

#include "../includes.h"

#include "handle.h"

namespace libredwgpp {

class EntityData
{
  public:
//    EntityData(uint8_t code = -1, uint32_t value = -1);

  public:
    void addHandle(const Handle& handle)
    {
      vHandles_.push_back(handle);
    }
//    size_t getCode() const { return code_; }
//
//    size_t getValue() const { return value_; }

  private:
    std::vector<Handle> vHandles_;

};

////////////////////////////////////////////////////////////////

}
