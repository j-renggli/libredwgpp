#include "parser.h"

#include "decoder.h"
#include "dwgbuffer.h"
#include "r2000/parser2000.h"
#include "r2004/parser2004.h"
#include "sections/classes.h"

#include <file/archive.h>
#include <schema/schema.h>

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Parser::Parser(Archive& archive) :
archive_(archive)
{
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser::create(Archive& archive, boost::shared_ptr<Parser>& ptrLoader)
{
  // Clear the pointer
  ptrLoader.reset();

  // Get version of file
  const size_t size = 6;

  core::MemBuffer buffer;
  core::ResultCode rc = archive.read(buffer, 0, size);
  if (rc.isFailure())
  {
    LOG_ERROR("Failed to read release number");
    return rc;
  }

  if (memcmp(buffer.getBuffer(), "AC1012", size) == 0) {
    LOG_ERROR("12");
    //header.version_ = Header::R13;
  } else if (memcmp(buffer.getBuffer(), "AC1014", size) == 0) {
    LOG_ERROR("14");
//    header.version_ = Header::R14;
  } else if (memcmp(buffer.getBuffer(), "AC1015", size) == 0) {
    ptrLoader.reset(new Parser2000(archive));
  } else if (memcmp(buffer.getBuffer(), "AC1018", size) == 0) {
    ptrLoader.reset(new Parser2004(archive));
//  } else {
//    return rcVersionError;
  }

  if (ptrLoader == NULL)
    return rcVersionError;

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser::parse()
{
  ptrSchema_.reset(new Schema);

  LOG_DEBUG("FileHeader");
  core::ResultCode rc = parseFileHeader();
  if (rc.isFailure())
    return rc;

  LOG_DEBUG("Map");
  rc = parseMap();
  if (rc.isFailure())
    return rc;

  LOG_DEBUG("Info");
  rc = parseInfo();
  if (rc.isFailure())
    return rc;

  LOG_DEBUG("Classes");
  rc = parseClasses();
  if (rc.isFailure())
    return rc;

  LOG_DEBUG(ptrClasses_->getClasses().size() << " classes");

  LOG_DEBUG("Objects");
  ptrObjects_.reset(new ObjectsParser(version_));
  rc = parseObjects(*ptrObjects_);
  if (rc.isFailure())
    return rc;

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser::parseClasses()
{
  DWGBuffer buffer;
  core::ResultCode rc = getSectionBuffer(Section::Classes, buffer);
  if (rc.isFailure())
    return rc;

  ptrClasses_.reset(new ClassesParser(version_));
  return ptrClasses_->restore(buffer);
}

////////////////////////////////////////////////////////////////

//core::ResultCode Parser::parseObjects()
//{
//  ptrObjects_.reset(new ObjectsParser(version_));
//
//  DWGBuffer buffer;
//  core::ResultCode rc = getSectionBuffer(Section::Objects, buffer);
//  if (rc.isFailure())
//    return rc;
//
//  return ptrObjects_->restore(buffer);
//}

////////////////////////////////////////////////////////////////

core::ResultCode Parser::parsePreview()
{
//  int nextPart = previewOffset_;
//
//  ////////////////
//  // Preview data
//  ////////////////
//  core::MemBuffer buffer;
//  core::ResultCode rc = archive_.read(buffer, nextPart, 21);
//  if (rc.isFailure())
//    return rc;
//
//  {
//    unsigned char expected[16] = {0x1F,0x25,0x6D,0x07,0xD4,0x36,0x28,0x28,0x9D,0x57,0xCA,0x3F,0x9D,0x44,0x10,0x2B};
//    if (memcmp(buffer.getBuffer(), expected, 16) != 0)
//      return core::rcFailure;
//  }
//
//  buffer.setPosition(16);
//  int32_t overallSize = buffer.read<int32_t>(false);
//  LOG_DEBUG("Overall size " << overallSize);
//
//  int8_t imageCount = buffer.read<int8_t>(false);
//  rc = archive_.read(buffer, nextPart + 21, imageCount * 9);
//  if (rc.isFailure())
//    return rc;
//
//  for (int8_t image = 0; image < imageCount; ++image)
//  {
//    int8_t type = buffer.read<int8_t>(false);
//
//    int32_t start = buffer.read<int32_t>(false);
//    int32_t size = buffer.read<int32_t>(false);
//
////    switch (type)
//    {
////      case 1: // header
//      {
//        if (start + size > nextPart)
//          nextPart = start + size;
//      }
//    }
//  }
//
//  ////////////////
//  // VBA project section
//  ////////////////
//  rc = archive_.read(buffer, nextPart, 16);
//  if (rc.isFailure())
//    return rc;
//
//  {
//    unsigned char expected[16] = {0xE0,0xDA,0x92,0xF8,0x2B,0xc9,0xD7,0xD7,0x62,0xA8,0x35,0xC0,0x62,0xBB,0xEF,0xD4};
//    if (memcmp(buffer.getBuffer(), expected, 16) != 0)
//      return core::rcFailure;
//  }
//
  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}
