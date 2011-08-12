#pragma once

#include "entity.h"

namespace libredwg2 {

namespace parserobject {

class Face3D : public Entity
{
  public:
    ~Face3D() {}

  public:
//    virtual core::ResultCode restoreFull(DWGBuffer& buffer, boost::shared_ptr<libredwg2::Object>& ptrObject, const Version& version) const;
    virtual core::ResultCode restoreFull(Schema& schema, DWGBuffer& buffer, const Colour& colour, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
