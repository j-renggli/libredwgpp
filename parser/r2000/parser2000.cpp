#include "parser2000.h"

#include <file/archive.h>

#include "../dwgbuffer.h"
//#include "decoder2004_2.h"
//#include "sectionclasses.h"
//#include "sectioninfo.h"
//#include "sectionmap.h"
//#include "sectionobjects.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Parser2000::Parser2000(Archive& archive) :
Parser(archive)
{
}

////////////////////////////////////////////////////////////////

Parser2000::~Parser2000()
{
}

////////////////////////////////////////////////////////////////

boost::shared_ptr<Decoder> Parser2000::getDecoder(int method)
{
  LOG_ERROR("TODO");
  return boost::shared_ptr<Decoder>();
//  return boost::shared_ptr<Decoder2004_2>(new Decoder2004_2);
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2000::parseFileHeader()
{
  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2000::parseInfo()
{
//  if (ptrMap_ == NULL)
//  {
//    LOG_ERROR("No section map to be found");
//    return core::rcFailure;
//  } else if (ptrInfo_ != NULL) {
//    LOG_ERROR("Section info already exists");
//    return core::rcFailure;
//  }
//
//  const Page* pPage = ptrMap_->findPage(id);
//  if (pPage == NULL)
//  {
//    LOG_ERROR("Could not find section info with id " << id);
//    return core::rcFailure;
//  }
//
//  ptrInfo_.reset(new SectionInfo(archive_, *pPage));
//  return ptrInfo_->restore();
  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

core::ResultCode Parser2000::parseMap()
{
  // Go to just after revision number
  core::MemBuffer buffer;
  core::ResultCode rc = archive_.read(buffer, 21, 4);
  if (rc.isFailure())
    return rc;

  size_t maxRecords = buffer.read<uint32_t>(false);
  rc = archive_.read(buffer, 25, 9 * maxRecords);
  if (rc.isFailure())
    return rc;

  for (size_t i = 0; i < maxRecords; ++i)
  {
    Page page;
    page.id_ = buffer.read<uint8_t>(false);
    page.offset_ = buffer.read<uint32_t>(false);
    page.size_ = buffer.read<uint32_t>(false);

    vPages_.push_back(page);
//    LOG_DEBUG((uint16_t)page.id_ << " " << std::hex << page.offset_ << " " << page.size_);
  }

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

//core::ResultCode Parser2004::parseClasses()
//{
//  // If info, then map !
//  if (ptrInfo_ == NULL)
//  {
//    LOG_ERROR("No section info to be found");
//    return core::rcFailure;
//  }
//
//  const SectionInfo::Subsection* pClassSec = ptrInfo_->findSubsection(SectionInfo::Subsection::CLASSES);
//  if (pClassSec == NULL)
//  {
//    LOG_ERROR("Could not find classes' subsection ");
//    return core::rcFailure;
//  }
//  SectionClasses sc(archive_, pClassSec->getPages());
//  core::ResultCode rc = sc.restoreMultiple(*ptrMap_);
//  return rc;
//}

////////////////////////////////////////////////////////////////

//template <int N>
core::ResultCode parseObject(DWGBuffer& data)//Object& parent)
{
  LOG_DEBUG("object");
  size_t bitsize = data.readRaw32();
  Handle handle = data.readHandle();
  LOG_DEBUG("bitsize " << bitsize);
  LOG_DEBUG("handle " << (int16_t)handle.code_ << " " << handle.value_);

  uint32_t fullSize = 0;
  while (true)
  {
    uint32_t size = data.readBit16();
    if (size == 0)
      break;

    fullSize += size;
//    if (fullSize == 0) {
//      fullSize = size;
//    } else {
//
//    }
    Handle h = data.readHandle();
    LOG_DEBUG("size " << size);
    LOG_DEBUG("handle " << (int16_t)h.code_ << " " << h.value_);
    std::string strToRemove;
    for (size_t i = fullSize - size; i < fullSize; ++i)
    {
      // Do something more with it...
      strToRemove.push_back((char)data.readRaw8()); if (!isprint(strToRemove[i])) strToRemove[i] = '-';
    }
    LOG_DEBUG(strToRemove);
  }

  return core::rcSuccess;
}
////////////////////////////////////////////////////////////////

//template <int N>
core::ResultCode parseEntity(DWGBuffer& data)//Object& parent)
{
  LOG_DEBUG("entity");
  size_t bitsize = data.readRaw32();
  Handle handle = data.readHandle();
  LOG_DEBUG("bitsize " << bitsize);
  LOG_DEBUG("handle " << (int16_t)handle.code_ << " " << handle.value_);

  uint32_t fullSize = 0;
  while (true)
  {
    uint32_t size = data.readBit16();
    if (size == 0)
      break;

    fullSize += size;
//    if (fullSize == 0) {
//      fullSize = size;
//    } else {
//
//    }
    Handle h = data.readHandle();
    LOG_DEBUG("size " << size);
    LOG_DEBUG("handle " << (int16_t)h.code_ << " " << h.value_);
    std::string strToRemove;
    for (size_t i = fullSize - size; i < fullSize; ++i)
    {
      // Do something more with it...
      strToRemove.push_back((char)data.readRaw8()); if (!isprint(strToRemove[i])) strToRemove[i] = '-';
    }
    LOG_DEBUG(strToRemove);
  }

  bool hasPicture = data.readBit();
  LOG_DEBUG("pic " << hasPicture);
  if (hasPicture)
  {
    size_t picSize = data.readRaw32();
    core::MemBuffer picture;
    picture.reserve(picSize);
    for (size_t i = 0; i < picSize; ++i)
      picture.write(data.readRaw8());
  }

  int mode = data.readBit2();
  int numReac = data.readBit32();
  bool noLinks = data.readBit();
  Colour colour = data.readColour();
  double lineScale = data.readBitDouble();
  int lineFlags = data.readBit2();
  int plotFlags = data.readBit2();
  int invisible = data.readBit16();
  int lineWeight = data.readRaw8();
  LOG_DEBUG(mode << " " << numReac << " " << noLinks << " " << colour.index_ << " " << std::fixed << std::setprecision(6) << lineScale << " " << lineFlags << " " << plotFlags << " " << invisible << " " << lineWeight);

  return core::rcSuccess;
}

core::ResultCode Parser2000::parseObjects()
{
  if (vPages_.size() < OBJECT + 1)
  {
    LOG_ERROR("Not enough pages " << vPages_.size());
    return core::rcFailure;
  }
//LOG_DEBUG("Address " << std::hex << vPages_[OBJECT].offset_);
//LOG_DEBUG("End     " << std::hex << (vPages_[OBJECT].offset_ + vPages_[OBJECT].size_));
  DWGBuffer data;
//  core::MemBuffer buffer;
  core::ResultCode rc = archive_.read(data.getBuffer(), vPages_[OBJECT].offset_, vPages_[OBJECT].size_);

  DWGBuffer objData;

  while (true)
  {
    size_t start = data.getPosition();

    uint32_t sgdc0 = data.readRaw8();
    uint32_t sgdc1 = data.readRaw8();
    uint32_t sectionSize = (sgdc0 << 8) | sgdc1;
    LOG_DEBUG("Section size " << sectionSize << " start " << start);// LOG_DEBUG((data.getPosition() - start));
//    if (sectionSize <= 2)
//      break;
    uint32_t address = 0;
    while (data.getPosition() - start < sectionSize)
    {
      int asdf = data.readModularChar();
      int addroff = data.readModularChar();
      address += addroff;
      LOG_DEBUG("pvztkt " << asdf << " pvzadr " << addroff << " means " << address);

      objData.setPosition(0);
      rc = archive_.read(objData.getBuffer(), address, 4096, false);
      if (rc.isFailure())
        return rc;
//      parseObject(
//      // DO something here...
////          dwg_decode_add_object(dwg, dat, last_address);
int objSize = objData.readModularShort();
uint16_t type = objData.readBit16();
LOG_DEBUG("type " << type << " / " << objSize);
if (type >= 500)
{
//    if (!dwg_decode_variable_type(dwg, dat, obj))
//      {
//        LOG_INFO("Object UNKNOWN:\n")
//
//        SINCE(R_2000)
//          {
//            bit_read_RL(dat);  // skip bitsize
//          }
//
//        if (!bit_read_H(dat, &obj->handle))
//          {
//            LOG_INFO("Object handle: %x.%x.%lx\n",
//              obj->handle.code, obj->handle.size, obj->handle.value)
//          }
//
//        obj->supertype = DWG_SUPERTYPE_UNKNOWN;
//        obj->tio.unknown = (unsigned char*)malloc(obj->size);
//        memcpy(obj->tio.unknown, &dat->chain[object_address], obj->size);
//      }
}
if (type <= 7 || type == 17 || type == 18 || type == 19 || type == 27 || type == 34 || type == 35 || type == 36 || type == 37 || type == 40 || type == 41 || type == 44 || type == 77 || type == 78)
  parseEntity(objData);
else
  parseObject(objData);
//break;
    }

    data.skipBits();
    sgdc0 = data.readRaw8();
    sgdc1 = data.readRaw8();
    uint32_t ckr = (sgdc0 << 8) | sgdc1;

//      sgdc[0] = bit_read_RC(dat);
//      sgdc[1] = bit_read_RC(dat);
//      ckr = (sgdc[0] << 8) | sgdc[1];
//
//      ckr2 = bit_ckr8(0xc0c1, dat->chain + duabyte, section_size);
//
//      if (ckr != ckr2)
//        {
//          printf("section %d crc todo ckr:%x ckr2:%x\n",
//                  dwg->header.section[2].number, ckr, ckr2);
//          return -1;
//        }
//
//      if (dat->byte >= maplasta)
//        break;
//
    if (sectionSize <= 2) break; //TODO
  }

//  maplasta = dat->byte + dwg->header.section[2].size; // 4
//  dwg->num_objects = 0;
//  object_begin = dat->size;
//  object_end = 0;
//  do
//    {
//      long unsigned int last_address;
//      long unsigned int last_handle;
//      long unsigned int previous_address = 0;
//
//      duabyte = dat->byte;
//      //LOG_TRACE("section_size: %u\n", section_size)
//      if (section_size > 2035)
//          return -1;
//
//      last_handle = 0;
//      last_address = 0;
//      while (dat->byte - duabyte < section_size)
//        {
//          long unsigned int kobj;
//          long int pvztkt;
//          long int pvzadr;
//
//          previous_address = dat->byte;
//          pvztkt = bit_read_MC(dat);
//          last_handle += pvztkt;
//          pvzadr = bit_read_MC(dat);
//          last_address += pvzadr;
//          // LOG_TRACE("Idc: %li\t", dwg->num_objects)
//          // LOG_TRACE("Handle: %li\tAddress: %li", pvztkt, pvzadr)
//          //}
//          if (dat->byte == previous_address)
//            break;
//          //if (dat->byte - duabyte >= seksize)
//          //break;
//
//          if (object_end < last_address)
//            object_end = last_address;
//          if (object_begin > last_address)
//            object_begin = last_address;
//
//          kobj = dwg->num_objects;
//          dwg_decode_add_object(dwg, dat, last_address);
//          //if (dwg->num_objects > kobj)
//          //dwg->object[dwg->num_objects - 1].handle.value = lastahandle;
//          //TODO: blame Juca
//        }
//      if (dat->byte == previous_address)
//        break;
//
//      // CRC on
//      if (dat->bit > 0)
//        {
//          dat->byte += 1;
//          dat->bit = 0;
//        }
//
//      sgdc[0] = bit_read_RC(dat);
//      sgdc[1] = bit_read_RC(dat);
//      ckr = (sgdc[0] << 8) | sgdc[1];
//
//      ckr2 = bit_ckr8(0xc0c1, dat->chain + duabyte, section_size);
//
//      if (ckr != ckr2)
//        {
//          printf("section %d crc todo ckr:%x ckr2:%x\n",
//                  dwg->header.section[2].number, ckr, ckr2);
//          return -1;
//        }
//
//      if (dat->byte >= maplasta)
//        break;
//    }
//  while (section_size > 2);






//  // If info, then map !
//  if (ptrInfo_ == NULL)
//  {
//    LOG_ERROR("No section info to be found");
//    return core::rcFailure;
////  } else if (ptrObjects_ != NULL) {
////    LOG_ERROR("Section objects already exists");
////    return core::rcFailure;
//  }
//
//  const SectionInfo::Subsection* pObjSec = ptrInfo_->findSubsection(SectionInfo::Subsection::OBJECTS);
//  if (pObjSec == NULL)
//  {
//    LOG_ERROR("Could not find objects' subsection ");
//    return core::rcFailure;
//  }
//  SectionObjects so(archive_, pObjSec->getPages());
//LOG_DEBUG("c/e " << pObjSec->isCompressed() << " " << pObjSec->isEncrypted());
//  core::ResultCode rc = so.restoreMultiple(*ptrMap_);
//  return rc;

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

//  long unsigned int previous_address;
//  long unsigned int object_address;
//  unsigned char previous_bit;
//  Dwg_Object *obj;
//
//  /* Keep the previous address
//   */
//  previous_address = dat->byte;
//  previous_bit = dat->bit;
//
//  /* Use the indicated address for the object
//   */
//  dat->byte = address;
//  dat->bit = 0;
//
//  /*
//   * Reserve memory space for objects
//   */
//  if (dwg->num_objects == 0)
//    dwg->object = (Dwg_Object *) malloc(sizeof(Dwg_Object));
//  else
//    dwg->object = (Dwg_Object *) realloc(dwg->object, (dwg->num_objects + 1)
//        * sizeof(Dwg_Object));
//
//  if (loglevel)
//      LOG_INFO("\n\n======================\nObject number: %lu",
//          dwg->num_objects)
//
//  obj = &dwg->object[dwg->num_objects];
//  obj->index = dwg->num_objects;
//  dwg->num_objects++;
//
//  obj->handle.code = 0;
//  obj->handle.size = 0;
//  obj->handle.value = 0;
//
//  obj->parent = dwg;
//  obj->size = bit_read_MS(dat);
//  object_address = dat->byte;
//  ktl_lastaddress = dat->byte + obj->size; /* (calculate the bitsize) */
//  obj->type = bit_read_BS(dat);
//
//  LOG_INFO(" Type: %d\n", obj->type)
}
