#include "colour.h"

namespace libredwgpp {

Colour::IndexMap Colour::s_Index2RGB;

////////////////////////////////////////////////////////////////

void Colour::initialiseIndexMap()
{
  s_Index2RGB[1] = 0xFF0000FF;
  s_Index2RGB[2] = 0xFFFF00FF;
  s_Index2RGB[3] = 0x00FF00FF;
  s_Index2RGB[4] = 0x00FFFFFF;
  s_Index2RGB[5] = 0x0000FFFF;
  s_Index2RGB[6] = 0xFF00FFFF;
  s_Index2RGB[9] = 0xC0C0C0FF;
  s_Index2RGB[7] = 0xFFFFFFFF;
  s_Index2RGB[10] = 0xFF0000FF;
  s_Index2RGB[11] = 0xFF7F7FFF;
  s_Index2RGB[13] = 0xCC6666FF;
  s_Index2RGB[14] = 0x990000FF;
  s_Index2RGB[15] = 0x994C4CFF;
}

////////////////////////////////////////////////////////////////

void Colour::setBookName(const UnicodeString& strName)
{
  strBookName_ = strName;
}

////////////////////////////////////////////////////////////////

void Colour::setIndex(uint32_t index)
{
  size_t rgba = s_Index2RGB[index];

  r_ = (rgba >> 24) & 0xFF;
  g_ = (rgba >> 16) & 0xFF;
  b_ = (rgba >> 8) & 0xFF;
  a_ = (rgba >> 0) & 0xFF;
  if (index == 0)
  {
    LOG_ERROR("0 index !!!");
  } else if (index > 7 && index != 9 && index != 10 && index != 11 && index != 13 && index != 14 && index != 15)
  {
    LOG_DEBUG(index << " => " << (size_t)r_ << " " << (size_t)g_ << " " << (size_t)b_ << " " << (size_t)a_);
  }
}

////////////////////////////////////////////////////////////////

void Colour::setName(const UnicodeString& strName)
{
  strName_ = strName;
}

////////////////////////////////////////////////////////////////

void Colour::setRGBA(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  r_ = r;
  g_ = g;
  b_ = b;
  a_ = a;
}

////////////////////////////////////////////////////////////////

}
