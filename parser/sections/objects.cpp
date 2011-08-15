#include "objects.h"

#include "classes.h"

#include "../dwgbuffer.h"

#include "../objects/blockcontrol.h"
#include "../objects/dictionary.h"
#include "../objects/face3d.h"
#include "../objects/layer.h"
#include "../objects/line.h"
#include "../objects/shapefile.h"
#include "../objects/undocumentedcontrol.h"
#include "../objects/vertex3d.h"

namespace libredwgpp {

////////////////////////////////////////////////////////////////

ObjectsParser::ObjectsParser(const Version& version) :
version_(version)
{
  mObjects_[11] = boost::shared_ptr<parserobject::Vertex3D>(new parserobject::Vertex3D);
  mObjects_[19] = boost::shared_ptr<parserobject::Line>(new parserobject::Line);
  mObjects_[28] = boost::shared_ptr<parserobject::Face3D>(new parserobject::Face3D);
  mObjects_[42] = boost::shared_ptr<parserobject::Dictionary>(new parserobject::Dictionary);
  mObjects_[48] = boost::shared_ptr<parserobject::BlockControl>(new parserobject::BlockControl);
  mObjects_[50] = boost::shared_ptr<parserobject::UndocumentedControl>(new parserobject::UndocumentedControl("LayerControl"));
  mObjects_[51] = boost::shared_ptr<parserobject::Layer>(new parserobject::Layer);
  mObjects_[52] = boost::shared_ptr<parserobject::UndocumentedControl>(new parserobject::UndocumentedControl("ShapeFileControl"));
  mObjects_[53] = boost::shared_ptr<parserobject::ShapeFile>(new parserobject::ShapeFile);
  mObjects_[56] = boost::shared_ptr<parserobject::UndocumentedControl>(new parserobject::UndocumentedControl("LineTypeControl"));
  mObjects_[60] = boost::shared_ptr<parserobject::UndocumentedControl>(new parserobject::UndocumentedControl("ViewControl"));
  mObjects_[62] = boost::shared_ptr<parserobject::UndocumentedControl>(new parserobject::UndocumentedControl("UCSControl"));
  mObjects_[64] = boost::shared_ptr<parserobject::UndocumentedControl>(new parserobject::UndocumentedControl("Table_vport"));
  mObjects_[66] = boost::shared_ptr<parserobject::UndocumentedControl>(new parserobject::UndocumentedControl("Table_appid"));
  mObjects_[68] = boost::shared_ptr<parserobject::UndocumentedControl>(new parserobject::UndocumentedControl("DimstyleControl"));
}

////////////////////////////////////////////////////////////////

std::map<int, int> mapx;

core::ResultCode ObjectsParser::restoreObject(Schema& schema, DWGBuffer& buffer, const ClassesParser& classes)
{
  size_t objectSize = buffer.readModularShort();
  size_t type = buffer.readBit16();

  if (mapx.find(type) == mapx.end())
  {
    mapx[type] = 0;
  } else {
    mapx[type] = mapx[type] + 1;
  }

  if (type >= 10 && type <= 19)
  {
//  LOG_DEBUG("type " << type << " / " << objectSize);
  }
  if (version_.isAtLeast(Version::R2010))
  {
    size_t handleStreamSize = buffer.readModularChar();
  }

  if (type >= 500)
  {
    const std::vector<Class>& vClasses = classes.getClasses();
    if (type - 500 >= vClasses.size())
    {
      LOG_NON_FATAL("Can't restore class object " << (type - 500));
      return core::rcSuccess;
    }

//    LOG_DEBUG(vClasses[type - 500].getAppName());
//    LOG_DEBUG(vClasses[type - 500].getCppName());
//    LOG_DEBUG(vClasses[type - 500].getDxfName());
    return core::rcSuccess;
  }

  ObjectsMap::const_iterator it = mObjects_.find(type);
  if (it == mObjects_.end())
  {
//    LOG_NON_FATAL("Unknown type " << type);
    return core::rcSuccess;
//    return core::rcFailure;
  }

  if (version_.isBetween(Version::R2000, Version::R2007))
  {
    size_t bitSize = buffer.readRaw32();
//    LOG_DEBUG("bitsize " << bitSize);
//LOG_DEBUG(buffer.getPosition() << ", " << buffer.getOffset());
  }
  Handle handle = buffer.readHandle();
//  LOG_DEBUG("handle " << (int16_t)handle.code_ << " " << handle.value_);

  uint32_t fullSize = 0;
  while (true)
  {
    uint32_t size = buffer.readBit16();
    if (size == 0)
      break;

    fullSize += size;
//    if (fullSize == 0) {
//      fullSize = size;
//    } else {
//
//    }
    Handle h = buffer.readHandle();
//    LOG_DEBUG("size " << size);
//    LOG_DEBUG("handle " << (int16_t)h.code_ << " " << h.value_);
    std::string strToRemove;
    for (size_t i = fullSize - size; i < fullSize; ++i)
    {
      // Do something more with it...
      strToRemove.push_back((char)buffer.readRaw8());
      if (!isprint(strToRemove[i]))
        strToRemove[i] = '-';
    }
    LOG_DEBUG(strToRemove);
  }

  core::ResultCode rc = it->second->restore(schema, buffer, version_);
  if (rc.isFailure())
    return rc;

//  LOG_DEBUG("OK");
//if (type <= 7 || type == 17 || type == 18 || type == 19 || type == 27 || type == 34 || type == 35 || type == 36 || type == 37 || type == 40 || type == 41 || type == 44 || type == 77 || type == 78)
//  parseEntity(objectData);
//else
//  parseObject(objectData);
//break;

  for (std::map<int, int>::iterator it = mapx.begin(); it != mapx.end(); ++it)
  {
//    LOG_DEBUG(it->first << " -> " << it->second);
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}
