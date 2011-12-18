#include "group.h"

#include "../version.h"

//#include <schema/face3d.h>
//#include <schema/schema.h>

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////
//R2000+:
//size of object in bits, not including end handles
//Common:
//Handle H 5
//EED X -3
//Length (char) followed by the handle bytes.
//See EED section.
//R13-R14 Only:
//Obj size RL size of object in bits, not including end handles
//Numreactors BL Number of persistent reactors attached to this obj
//Common:
//R2004+:
//XDic Missing Flag
//B
//If 1, no XDictionary handle is stored for this
//object, otherwise XDictionary handle is stored as in
//R2000 and earlier.
//Common:
//Str TV
//name of group
//Unnamed BS 1 if group has no name
//Selectable BS 1 if group selectable
//Numhandles BL # objhandles in this group
//Handle refs H parenthandle (soft pointer)
//[Reactors (soft pointer)]
//xdicobjhandle (hard owner)
//the entries in the group (hard pointer)

// P. 176
core::ResultCode Group::restoreFull(ISchema& schema, DWGBuffer& buffer, const Handle& handle, const Version& version) const
{
//  LOG_DEBUG("asdf");
  UnicodeString strName = buffer.readText(version);
  size_t unnammed = buffer.readBit16(); // Unnammed
  size_t selectable = buffer.readBit16(); // selectable
  size_t numhandles = buffer.readBit32();
//  LOG_DEBUG(strName << " " << unnammed << " " << selectable << " " << numhandles);
//
//  Handle h = buffer.readHandle();
//  LOG_DEBUG(h.getCode() << " " << h.getValue());
//  EntityData eed = buffer.readEED();
//  return core::rcFailure;
//    bool hasFlag = ~buffer.readBit();
//    bool skipZ = buffer.readBit();
//    double x = buffer.readRawDouble();
//    double y = buffer.readRawDouble();
//    double z = 0;
//    if (!skipZ)
//    {
//      z = buffer.readRawDouble();
//    }
//
//    corners[0] = libredwgpp::Vertex3d(x, y, z);
//
//    for (int i = 0; i < 3; ++i)
//    {
//      buffer.readBitDouble(x);
//      buffer.readBitDouble(y);
//      buffer.readBitDouble(z);
//      corners[i + 1] = libredwgpp::Vertex3d(x, y, z);
//    }
//
//    if (hasFlag)
//    {
//      invisibleEdgeFlag = buffer.readBit16();
//    }
//  } else {
//    libredwgpp::Vertex3d corners[4];
//
//    for (int i = 0; i < 4; ++i)
//    {
//      double x = buffer.readBitDouble();
//      double y = buffer.readBitDouble();
//      double z = buffer.readBitDouble();
//      corners[i] = libredwgpp::Vertex3d(x, y, z);
//    }
//
//    invisibleEdgeFlag = buffer.readBit16();
//  }
//
//  if (colour.getR() == 0 && colour.getG() > 0 && colour.getB() > 0)
//  {
//    LOG_DEBUG(handle.getValue() << ": " << handle.getCode() << " " << int(colour.getR()) << " " << int(colour.getG()) << " " << int(colour.getB()));
//  }
//  schema.addFace3d(libredwgpp::Face3d(handle.getValue(), colour, corners[0], corners[1], corners[2], corners[3]));

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
