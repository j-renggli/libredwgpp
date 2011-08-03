//#include "sectionclasses.h"
//
//#include "../dwgbuffer.h"
//#include "../version.h"
//
//namespace libredwg2 {
//
//uint8_t class_guard[16] = {0x8D, 0xA1, 0xC4, 0xB8, 0xC4, 0xA9, 0xF8, 0xC5, 0xC0, 0xDC, 0xF4, 0x5F, 0xE7, 0xCF, 0xB6, 0x8A};
//
//////////////////////////////////////////////////////////////////
//
//SectionClasses::SectionClasses(Archive& archive, const std::vector<Page>& multiple) :
//Section2004(archive, multiple)
//{
//}
//
//////////////////////////////////////////////////////////////////
//
//core::ResultCode SectionClasses::restoreData(DWGBuffer& data)
//{
//  //Verify guard
//  for (int j = 0; j < 16; ++j)
//  {
//    uint8_t c = data.readRaw8();
//    if (c != class_guard[j])
//    {
//      LOG_DEBUG("Wrong class guard");
//      return core::rcFailure;
//    }
//  }
//
//  uint32_t size = data.readRaw32();
//  uint16_t maxNum = data.readBit32();
////  data.readRaw8(); // 0;
////  data.readRaw8(); // 0;
//  data.readBit(); // 1;
////  LOG_DEBUG(size << " - size");
////  LOG_DEBUG(maxNum << " - maxNum");
//
//  while (data.hasMore())
//  {
//    uint16_t number = data.readBit16();
//    uint16_t proxyFlags = data.readBit16();
//    Version version(Version::R2004);
//    UnicodeString strAppName = data.readText(version);
//    UnicodeString strCppName = data.readText(version);
//    UnicodeString strDxfName = data.readText(version);
////    std::string strAppName, strCppName, strDxfName;
////    data.readText(strAppName);
////    data.readText(strCppName);
////    data.readText(strDxfName);
//    bool isZombie = data.readBit();
//    uint16_t cid = data.readBit16();
//
//    uint32_t nObj = data.readBit32();
//    uint16_t dwgVer = data.readBit16();
//    uint16_t maintenance = data.readBit16();
//    data.readBit32();
//    data.readBit32();
////
////    LOG_DEBUG(number << " " << proxyFlags);
////    LOG_DEBUG(strAppName << " " << strCppName << " " << strDxfName);
////    LOG_DEBUG(nObj << " " << dwgVer << " " << maintenance);
//
//    if (number == maxNum)
//      break;
//  }
//
//  return core::rcSuccess;
//}
//
//////////////////////////////////////////////////////////////////
//
//}
