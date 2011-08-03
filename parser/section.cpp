#include "section.h"

namespace libredwg2 {

std::map<std::string, Section::Type> Section::s_mapTypes;

////////////////////////////////////////////////////////////////

Section::Type Section::findType(const std::string& strName)
{
  if (s_mapTypes.empty())
  {
//    s_mapTypes["AcDb:FileDepList"] = FILEDEPS;
//    s_mapTypes["AcDb:AppInfoHistory"] = APPINFOHISTORY;
//    s_mapTypes["AcDb:AppInfo"] = APPINFO;
//    s_mapTypes["AcDb:Preview"] = PREVIEW;
//    s_mapTypes["AcDb:SummaryInfo"] = SUMMARY;
//    s_mapTypes["AcDb:RevHistory"] = REVHISTORY;
    s_mapTypes["AcDb:AcDbObjects"] = Objects;
//    s_mapTypes["AcDb:ObjFreeSpace"] = OBJFREESPACE;
//    s_mapTypes["AcDb:Template"] = TEMPLATE;
//    s_mapTypes["AcDb:Handles"] = HANDLES;
    s_mapTypes["AcDb:Classes"] = Classes;
//    s_mapTypes["AcDb:AuxHeader"] = AUXHEADER;
//    s_mapTypes["AcDb:Header"] = HEADER;
//    s_mapTypes[""] = ;
//    s_mapTypes[""] = ;
  }

  std::map<std::string, Type>::const_iterator it = s_mapTypes.find(strName);
  if (it == s_mapTypes.end())
    return Unknown;
  else
    return it->second;
}

////////////////////////////////////////////////////////////////

}
