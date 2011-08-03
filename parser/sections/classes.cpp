#include "classes.h"

#include "../dwgbuffer.h"

namespace libredwg2 {

static uint8_t class_parser_guard[16] = {0x8D, 0xA1, 0xC4, 0xB8, 0xC4, 0xA9, 0xF8, 0xC5, 0xC0, 0xDC, 0xF4, 0x5F, 0xE7, 0xCF, 0xB6, 0x8A};

////////////////////////////////////////////////////////////////

ClassesParser::ClassesParser(const Version& version) :
version_(version)
{
}

////////////////////////////////////////////////////////////////

//SectionClasses::SectionClasses(Archive& archive, const std::vector<Page>& multiple) :
//Section2004(archive, multiple)
//{
//}

////////////////////////////////////////////////////////////////

core::ResultCode ClassesParser::restore(DWGBuffer& data)
{
  if (!vClasses_.empty())
  {
    LOG_ERROR("Classes already parsed");
    return rcAlreadyParsed;
  }

  //Verify guard
  for (int j = 0; j < 16; ++j)
  {
    const uint8_t c = data.readRaw8();
    if (c != class_parser_guard[j])
    {
      LOG_DEBUG("Wrong class guard");
      return rcWrongGuard;
    }
  }

  const size_t size = data.readRaw32();

  if (version_.isGreaterThan(Version::R2010, 3))
  {
    data.readRaw32();
  }

  size_t maxNum = size_t(-1);
  const bool is2004 = version_.isAtLeast(Version::R2004);
  if (is2004)
  {
    maxNum = data.readBit32();
  //  data.readRaw8(); // 0;
  //  data.readRaw8(); // 0;
    data.readBit(); // 1;
  //  LOG_DEBUG(size << " - size");
  //  LOG_DEBUG(maxNum << " - maxNum");
    vClasses_.reserve(std::min(size_t(100), maxNum));
  }

  const size_t start = data.getPosition();
  while (data.getPosition() < start + size)
  {
    const uint16_t number = data.readBit16();
    const uint16_t flags = data.readBit16();
    const UnicodeString strAppName = data.readText(version_);
    const UnicodeString strCppName = data.readText(version_);
    const UnicodeString strDxfName = data.readText(version_);
    const bool wasZombie = data.readBit();
    const uint16_t cid = data.readBit16();

    vClasses_.push_back(Class(number, flags, strAppName, strCppName, strDxfName, wasZombie, cid));

    if (is2004)
    {
      const uint32_t nObj = data.readBit32();
      const uint16_t dwgVer = data.readBit16();
      const uint16_t maintenance = data.readBit16();
      data.readBit32();
      data.readBit32();

//      vClasses_.back().addInfo(nObj, dwgVer, maintenance);
    }

    if (number == maxNum)
      break;
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}
