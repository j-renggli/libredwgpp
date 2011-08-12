#include "face3d.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Face3d::Face3d(const Colour& col, const Vertex3d& c1, const Vertex3d& c2, const Vertex3d& c3, const Vertex3d& c4) :
colour_(col)
{
  apex_[0] = c1;
  apex_[1] = c2;
  apex_[2] = c3;
  apex_[3] = c4;
}

////////////////////////////////////////////////////////////////

}
