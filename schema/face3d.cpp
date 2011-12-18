#include "face3d.h"

namespace libredwgpp {

////////////////////////////////////////////////////////////////

Face3d::Face3d(size_t id, const Colour& col, const Vertex3d& c1, const Vertex3d& c2, const Vertex3d& c3, const Vertex3d& c4) :
id_(id),
colour_(col)
{
  apex_[0] = c1;
  apex_[1] = c2;
  apex_[2] = c3;
  apex_[3] = c4;
}

////////////////////////////////////////////////////////////////

}
