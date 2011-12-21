#pragma once

#include "entity.h"
#include "object.h"

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

class Block : public parserobject::Entity
{
  public:
    ~Block() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const;
};

////////////////////////////////////////////////////////////////

class EndBlock : public parserobject::Entity
{
  public:
    ~EndBlock() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const;
};

////////////////////////////////////////////////////////////////

class BlockControl : public parserobject::Object
{
  public:
    ~BlockControl() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const;
};

////////////////////////////////////////////////////////////////

class BlockHeader : public parserobject::Object
{
  public:
    ~BlockHeader() {}

  public:
    virtual core::ResultCode restoreFull(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const;
};

////////////////////////////////////////////////////////////////

}

}
