#include "loader.h"

#include <parser/parser.h>

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Loader::Loader()
{
}

////////////////////////////////////////////////////////////////

Loader::~Loader()
{
}

////////////////////////////////////////////////////////////////

//core::ResultCode Loader::parseHeader(std::ifstream& fileIn, Header& header)
//{
//}

////////////////////////////////////////////////////////////////

core::ResultCode Loader::restore(const boost::filesystem::path& pathFile, boost::shared_ptr<Schema>& ptrSchema)
{
  // Basic tests
  if (!exists(pathFile) || !is_regular(pathFile))
  {
    return rcFileNotFound;
  }

  std::ifstream fileIn(pathFile.native_file_string().c_str(), std::ios::binary);
  if (!fileIn)
  {
    return rcInputError;
  }

  boost::shared_ptr<Parser> ptrParser;
  core::ResultCode rc = Parser::create(fileIn, ptrParser);
  if (rc.isFailure())
    return rc;

  ASSERT(ptrParser != NULL);

  rc = ptrParser->parse();
  if (rc.isFailure())
    return rc;
//  uiPos_ = 0;
//  uiSize_ = 4096;
//  char pTemp[4096];
//  while (true)
//  {
//    fileIn.read(pTemp, uiSize_);
//    if (fileIn.bad())
//    {
//      return rcFailure;
//    }
//
//    size_t uiCount = fileIn.gcount();
//    if (uiCount == 0)
//      break;
//    Buffer* pNewBuffer = new Buffer[uiPos_ + uiCount];
//    memcpy(pNewBuffer, pBuffer_, uiPos_);
//    memcpy(pNewBuffer+uiPos_, pTemp, uiCount);
//    delete[] pBuffer_;
//    pBuffer_ = pNewBuffer;
//    uiPos_ += uiCount;
//
//    if (uiCount < uiSize_)
//      break;
//  }
//
//  uiSize_ = uiPos_;
//  uiPos_ = 0;
//
//  fileIn.close();

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}
