#include "parser.h"

#include "decoder.h"
#include "parser2004.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Parser::Parser(std::ifstream& fileBuffer) :
fileBuffer_(fileBuffer)
{
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser::create(std::ifstream& fileBuffer, boost::shared_ptr<Parser>& ptrLoader)
{
  // Clear the pointer
  ptrLoader.reset();

  // Get version of file
  const size_t size = 6;
  char buffer[size];

  fileBuffer.read(buffer, size);

  if (strncmp(buffer, "AC1012", size) == 0) {
    //header.version_ = Header::R13;
  } else if (strncmp(buffer, "AC1014", size) == 0) {
//    header.version_ = Header::R14;
  } else if (strncmp(buffer, "AC1015", size) == 0) {
//    header.version_ = Header::R2000;
  } else if (strncmp(buffer, "AC1018", size) == 0) {
    ptrLoader.reset(new Parser2004(fileBuffer));
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
  fileBuffer_.seekg(6);

  const size_t maxBuffer = 4096;
  char buffer[maxBuffer];

  // Read multiple values
  fileBuffer_.read(buffer, 122);

  memcpy(&previewOffset_, &buffer[7], 4);
  memcpy(&codepage_, &buffer[13], 2);
  memcpy(&securityFlags_, &buffer[18], 4);
  memcpy(&summaryOffset_, &buffer[26], 4);
  int32_t verif;
  memcpy(&verif, &buffer[34], 4);
  if (verif != 0x80)
  {
    LOG_ERROR("Verification code " << verif);
    return core::rcFailure;
  }

  // Encoded data
  fileBuffer_.read(buffer, 108);

  int32_t randseed = 1;
  for (int b = 0; b < 108; ++b)
  {
    randseed *= 0x343fd;
    randseed += 0x269ec3;
    buffer[b] ^= (randseed >> 0x10);
  }

  if (strncmp(buffer, "AcFssFcAJMB", 11) != 0)
  {
    LOG_ERROR("Decoding failed");
    return core::rcFailure;
  }

  int32_t lastSecPid;
  int64_t lastSecPead;
  int64_t repeatedHeader;
  int32_t secPageMid;

  memcpy(&lastSecPid, &buffer[0x28], 4);
  memcpy(&lastSecPead, &buffer[0x2C], 8);
  memcpy(&repeatedHeader, &buffer[0x34], 8);
  memcpy(&secPageMid, &buffer[0x50], 4);

  memcpy(&sectionMapOffset_, &buffer[0x54], 4);
  sectionMapOffset_ += 0x100;

  ////////////////
  // System Section map
  ////////////////
  fileBuffer_.seekg(sectionMapOffset_);
  fileBuffer_.read(buffer, 20);
  memcpy(&verif, buffer, 4);
  if (verif != 0x41630e3b)
  {
    LOG_ERROR("Bad address leads to " << verif);
    return core::rcFailure;
  }

  int32_t sizeUncomp;
  int32_t sizeCompr;
  int32_t compressionType;
  int32_t checkSum;

  memcpy(&sizeUncomp, &buffer[4], 4);
  memcpy(&sizeCompr, &buffer[8], 4);
  memcpy(&compressionType, &buffer[12], 4);
  memcpy(&checkSum, &buffer[16], 4);

  core::MemBuffer compressed, clear;
  compressed.resize(sizeCompr);
  clear.resize(sizeUncomp);
  fileBuffer_.read((char*)compressed.getBuffer(), sizeCompr);

  boost::shared_ptr<Decoder> ptrDecoder = getDecoder(compressionType);
  ptrDecoder->decode(compressed, clear);

  clear.setPosition(0);

  // Parse section pages
  std::vector<std::pair<int, int> > vSections;
  int previous = 0x100;
  while (true)
  {
    int id = clear.read<int32_t>(false);
    int size = clear.read<int32_t>(false);

    LOG_DEBUG(id << "\t" << size);
  }
  LOG_DEBUG("sizeUncomp " << sizeUncomp);
  LOG_DEBUG("sizeCompr " << sizeCompr);
  LOG_DEBUG("compressionType " << compressionType);
  LOG_DEBUG("checkSum " << checkSum);


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
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser::parsePreview()
{
  int nextPart = previewOffset_;

  ////////////////
  // Preview data
  ////////////////
  fileBuffer_.seekg(nextPart);

  char sentinel[16];
  {
    unsigned char expected[16] = {0x1F,0x25,0x6D,0x07,0xD4,0x36,0x28,0x28,0x9D,0x57,0xCA,0x3F,0x9D,0x44,0x10,0x2B};
    fileBuffer_.read(sentinel, 16);
    if (memcmp(sentinel, expected, 16) != 0)
      return core::rcFailure;
  }

  int32_t overallSize;
  fileBuffer_.read((char*)(&overallSize), 4);
  LOG_DEBUG("Overall size " << overallSize);

  int8_t imageCount;
  fileBuffer_.read((char*)(&imageCount), 1);
  for (int8_t image = 0; image < imageCount; ++image)
  {
    int8_t type;
    fileBuffer_.read((char*)(&type), 1);

    int32_t start;
    int32_t size;

//    switch (type)
    {
//      case 1: // header
      {
        fileBuffer_.read((char*)(&start), 4);
        fileBuffer_.read((char*)(&size), 4);

        if (start + size > nextPart)
          nextPart = start + size;
      }
    }
  }

  ////////////////
  // VBA project section
  ////////////////
  fileBuffer_.seekg(nextPart);

  {
    unsigned char expected[16] = {0xE0,0xDA,0x92,0xF8,0x2B,0xc9,0xD7,0xD7,0x62,0xA8,0x35,0xC0,0x62,0xBB,0xEF,0xD4};
    fileBuffer_.read(sentinel, 16);
    if (memcmp(sentinel, expected, 16) != 0)
      return core::rcFailure;
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////

}
