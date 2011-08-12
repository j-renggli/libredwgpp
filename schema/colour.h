#pragma once

#include "../includes.h"

namespace libredwg2 {

class Colour
{
  public:
    void setBookName(const UnicodeString& strName);

    void setIndex(uint32_t index);

    void setName(const UnicodeString& strName);

    void setRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

  private:
    typedef std::map<uint32_t, uint32_t> IndexMap;

  private:
//    uint32_t index_;
//    uint32_t rgb_;
    uint8_t r_;
    uint8_t g_;
    uint8_t b_;
    uint8_t a_;
    UnicodeString strName_;
    UnicodeString strBookName_;

  public:
    static void initialiseIndexMap();

  private:
    static IndexMap s_Index2RGB;
};

////////////////////////////////////////////////////////////////

}
