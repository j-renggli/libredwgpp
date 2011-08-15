#pragma once

#include "entity.h"

namespace libredwgpp {

namespace parserobject {

class Face3D : public Entity
{
  public:
    ~Face3D() {}

  public:
//    virtual core::ResultCode restoreFull(DWGBuffer& buffer, boost::shared_ptr<libredwgpp::Object>& ptrObject, const Version& version) const;
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
