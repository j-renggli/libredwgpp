#include "archive.h"

#include <parser/parser.h>

#include <schema/colour.h>

namespace libredwgpp {

////////////////////////////////////////////////////////////////

Archive::Archive()
{
}

////////////////////////////////////////////////////////////////

Archive::~Archive()
{
}

////////////////////////////////////////////////////////////////

core::ResultCode Archive::read(core::IWriteBuffer& buffer, size_t pos, size_t len, bool strict)
{
//  if (pos > 824920 && pos < 825000)
////  if (pos > 859800 && pos < 859850)
//  {
//    LOG_DEBUG(pos << " --- " << len);
//  }

  if (pos + len > size_)
  {
    if (strict)
      return rcOutOfBounds;
    else
      len = size_ - pos;
  }

  buffer.resize(len);
  fileStream_.seekg(pos);
  fileStream_.read((char*)buffer.getBuffer(), len);
  buffer.setPosition(0);
  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Archive::restore(const boost::filesystem::path& pathFile, boost::shared_ptr<ISchema>& ptrSchema)
{
  // Basic tests
  if (!exists(pathFile) || !is_regular(pathFile))
  {
    LOG_ERROR("File not found: " << pathFile);
    return rcFileNotFound;
  }

  fileStream_.open(pathFile.string().c_str(), std::ios::binary);
  if (!fileStream_)
  {
    LOG_ERROR("File could not be loaded: " << pathFile);
    return rcInputError;
  }

  Colour::initialiseIndexMap();

  size_ = boost::filesystem::file_size(pathFile);

  boost::shared_ptr<Parser> ptrParser;
  core::ResultCode rc = Parser::create(*this, ptrParser);
  if (rc.isFailure())
    return rc;

  ASSERT(ptrParser != NULL);

  if (ptrSchema == NULL)
  {
    LOG_ERROR("Null schema not supported yet");
    return core::rcFailure;
  }

  return ptrParser->parse(*ptrSchema);
}

////////////////////////////////////////////////////////////////

}
