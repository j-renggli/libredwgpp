#include "errorcodes.h"

namespace libredwg2 {

core::ResultCode rcFileNotFound(core::ResultCode::eError, 200);
core::ResultCode rcInputError(core::ResultCode::eError, 201);
core::ResultCode rcVersionError(core::ResultCode::eError, 202);
core::ResultCode rcOutOfBounds(core::ResultCode::eError, 203);

}
