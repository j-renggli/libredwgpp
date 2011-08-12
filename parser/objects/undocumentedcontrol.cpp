#include "undocumentedcontrol.h"

namespace libredwg2 {

namespace parserobject {

////////////////////////////////////////////////////////////////

core::ResultCode UndocumentedControl::restoreFull(Schema& schema, DWGBuffer& buffer, const Version& version) const
{
  /*size_t numEntries = */buffer.readModularShort();
//  LOG_DEBUG(strName_ << " num entries " << numEntries);

  try
  {
    Handle handle = buffer.readHandle();
//    LOG_DEBUG(strName_ << " handle " << (int16_t)handle.code_ << " " << handle.value_);
  } catch (std::exception& e)
  {
  }

//Common:
//Numentries BL
//Handle refs
//70
//H
//Doesn't count *MODEL_SPACE and *PAPER_SPACE.
//NULL (soft pointer)
//xdicobjhandle (hard owner)
//numentries handles of blockheaders in the file (soft
//owner), then *MODEL_SPACE and *PAPER_SPACE (hard
//owner).
//CRC
//X
//---


  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
