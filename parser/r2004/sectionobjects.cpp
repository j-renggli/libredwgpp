#include "sectionobjects.h"

#include "../dwgbuffer.h"
#include "../version.h"

namespace libredwg2 {

const int32_t SectionObjects::s_guard = 0x4163043b;

////////////////////////////////////////////////////////////////

SectionObjects::SectionObjects(Archive& archive, const std::vector<Page>& multiple) :
Section2004(archive, multiple)
{
}

////////////////////////////////////////////////////////////////

core::ResultCode SectionObjects::restoreData(DWGBuffer& data)
{
  //Verify guard
  for (int j = 0; j < 16; ++j)
  {
    uint8_t c = data.readRaw8();
    LOG_DEBUG(std::hex << (uint16_t)c);
//    if (c != class_guard[j])
//    {
//      LOG_DEBUG("Wrong class guard");
//      return core::rcFailure;
//    }
  }

  uint32_t size = data.readRaw32();
  uint16_t maxNum = data.readBit32();
//  data.readRaw8(); // 0;
//  data.readRaw8(); // 0;
  data.readBit(); // 1;
//  LOG_DEBUG(size << " - size");
//  LOG_DEBUG(maxNum << " - maxNum");

  while (data.hasMore())
  {
    uint16_t number = data.readBit16();
    uint16_t proxyFlags = data.readBit16();
    Version version(Version::R2004);
    UnicodeString strAppName = data.readText(version);
    UnicodeString strCppName = data.readText(version);
    UnicodeString strDxfName = data.readText(version);
//    std::string strAppName, strCppName, strDxfName;
//    data.readText(strAppName);
//    data.readText(strCppName);
//    data.readText(strDxfName);
    bool isZombie = data.readBit();
    uint16_t cid = data.readBit16();

    uint32_t nObj = data.readBit32();
    uint16_t dwgVer = data.readBit16();
    uint16_t maintenance = data.readBit16();
    data.readBit32();
    data.readBit32();
//
//    LOG_DEBUG(number << " " << proxyFlags);
//    LOG_DEBUG(strAppName << " " << strCppName << " " << strDxfName);
//    LOG_DEBUG(nObj << " " << dwgVer << " " << maintenance);

    if (number == maxNum)
      break;
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}
