#include "parser2004.h"

#include "decoder2004_2.h"

namespace libredwg2 {

////////////////////////////////////////////////////////////////

Parser2004::Parser2004(std::ifstream& fileBuffer) :
Parser(fileBuffer)
{
}

////////////////////////////////////////////////////////////////

Parser2004::~Parser2004()
{
}

////////////////////////////////////////////////////////////////

boost::shared_ptr<Decoder> Parser2004::getDecoder(int method)
{
  return boost::shared_ptr<Decoder2004_2>(new Decoder2004_2);
}

//core::ResultCode Parser2004::parse()
//{
//  core::ResultCode rc = parsePreview();
//  if (rc.isFailure())
//    return rc;
//
//  return core::rcSuccess;
//}

////////////////////////////////////////////////////////////////

}
