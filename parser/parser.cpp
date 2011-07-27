#include "parser.h"

#include "decoder.h"
#include "r2004/parser2004.h"
#include "r2004/sectionpage.h"

#include <file/archive.h>

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
    //header.version_ = Header::R13;
  } else if (memcmp(buffer.getBuffer(), "AC1014", size) == 0) {
//    header.version_ = Header::R14;
  } else if (memcmp(buffer.getBuffer(), "AC1015", size) == 0) {
//    header.version_ = Header::R2000;
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
  // Go to just after revision number
  core::MemBuffer buffer;
  core::ResultCode rc = archive_.read(buffer, 6, 122);
  if (rc.isFailure())
    return rc;

  memcpy(&previewOffset_, &buffer.getBuffer()[7], 4);
  memcpy(&codepage_, &buffer.getBuffer()[13], 2);
  memcpy(&securityFlags_, &buffer.getBuffer()[18], 4);
  memcpy(&summaryOffset_, &buffer.getBuffer()[26], 4);
  int32_t verif;
  memcpy(&verif, &buffer.getBuffer()[34], 4);
  if (verif != 0x80)
  {
    LOG_ERROR("Verification code " << verif);
    return core::rcFailure;
  }

  // Encoded data
  rc = archive_.read(buffer, 128, 108);
  if (rc.isFailure())
    return rc;

  int32_t randseed = 1;
  for (int b = 0; b < 108; ++b)
  {
    randseed *= 0x343fd;
    randseed += 0x269ec3;
    buffer.getBuffer()[b] ^= (randseed >> 0x10);
  }

  if (memcmp(buffer.getBuffer(), "AcFssFcAJMB", 11) != 0)
  {
    LOG_ERROR("Decoding failed");
    return core::rcFailure;
  }

  int32_t lastSecPid;
  int64_t lastSecPead;
  int64_t repeatedHeader;
  int32_t secPageMid;
  int32_t secInfo;

  memcpy(&lastSecPid, &buffer.getBuffer()[0x28], 4);
  memcpy(&lastSecPead, &buffer.getBuffer()[0x2C], 8);
  memcpy(&repeatedHeader, &buffer.getBuffer()[0x34], 8);
  memcpy(&secPageMid, &buffer.getBuffer()[0x50], 4);
  memcpy(&sectionMapOffset_, &buffer.getBuffer()[0x54], 4);
  memcpy(&secInfo, &buffer.getBuffer()[0x5C], 4);
  sectionMapOffset_ += 0x100;

  ////////////////
  // System Section map
  ////////////////
  SectionPage sectionMap(archive_, sectionMapOffset_);
  rc = sectionMap.restore();
  if (rc.isFailure())
    return rc;

  // Test section 1:
//  rc = archive_.read(buffer, vSections[97].address_, vSections[97].size_);
//  if (rc.isFailure())
//    return rc;
//
//  memcpy(&verif, &buffer.getBuffer()[0], 4);
//  if (verif != 0x4163003b)
//  {
//    LOG_ERROR("Bad address leads to " << verif);
//    return core::rcFailure;
//  }
//  LOG_DEBUG("0x02 " << verif);
//  memcpy(&verif, &buffer.getBuffer()[8], 4);
//  LOG_DEBUG("0x7400 " << verif);
//  memcpy(&verif, &buffer.getBuffer()[12], 4);
//  LOG_DEBUG("0x0 " << verif);
//  int64_t xxx;
//  memcpy(&xxx, &buffer.getBuffer()[0x14], 4);
//  LOG_DEBUG("0x02 " << verif);


//
//  for (size_t i = 0; i < clear.getSize(); ++i) {
//    if (clear.getBuffer()[i] >= 'A' && clear.getBuffer()[i] <= 'z')
//      std::cout << (char)clear.getBuffer()[i];
//    else
//      std::cout << "[" << std::hex << (int16_t)clear.getBuffer()[i] << "]";
//  }

//  LOG_DEBUG("Preview at " << previewOffset_);
//  LOG_DEBUG("Codepage " << codepage_);
//  LOG_DEBUG("Security flags " << securityFlags_);
//  LOG_DEBUG("Summary offset " << summaryOffset_);
//
//  LOG_DEBUG("Section id " << lastSecPid);
//  LOG_DEBUG("Section address " << lastSecPead);
//  LOG_DEBUG("Rep. header " << repeatedHeader);
//  LOG_DEBUG("Page id " << secPageMid);
//  LOG_DEBUG("Page address " << sectionMapOffset_);
  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser::parsePreview()
{
  int nextPart = previewOffset_;

  ////////////////
  // Preview data
  ////////////////
  core::MemBuffer buffer;
  core::ResultCode rc = archive_.read(buffer, nextPart, 21);
  if (rc.isFailure())
    return rc;

  {
    unsigned char expected[16] = {0x1F,0x25,0x6D,0x07,0xD4,0x36,0x28,0x28,0x9D,0x57,0xCA,0x3F,0x9D,0x44,0x10,0x2B};
    if (memcmp(buffer.getBuffer(), expected, 16) != 0)
      return core::rcFailure;
  }

  buffer.setPosition(16);
  int32_t overallSize = buffer.read<int32_t>(false);
  LOG_DEBUG("Overall size " << overallSize);

  int8_t imageCount = buffer.read<int8_t>(false);
  rc = archive_.read(buffer, nextPart + 21, imageCount * 9);
  if (rc.isFailure())
    return rc;

  for (int8_t image = 0; image < imageCount; ++image)
  {
    int8_t type = buffer.read<int8_t>(false);

    int32_t start = buffer.read<int32_t>(false);
    int32_t size = buffer.read<int32_t>(false);

//    switch (type)
    {
//      case 1: // header
      {
        if (start + size > nextPart)
          nextPart = start + size;
      }
    }
  }

  ////////////////
  // VBA project section
  ////////////////
  rc = archive_.read(buffer, nextPart, 16);
  if (rc.isFailure())
    return rc;

  {
    unsigned char expected[16] = {0xE0,0xDA,0x92,0xF8,0x2B,0xc9,0xD7,0xD7,0x62,0xA8,0x35,0xC0,0x62,0xBB,0xEF,0xD4};
    if (memcmp(buffer.getBuffer(), expected, 16) != 0)
      return core::rcFailure;
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////

}
