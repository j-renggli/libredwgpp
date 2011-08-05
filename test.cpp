#include <iostream>

#include <core/include/log/coutdisplay.h>

#include "file/archive.h"

#include "schema/schema.h"



//#include "libredwg/src/dwg.h"

int main(int argc, char* argv[])
{

//  unsigned int i;
//  int success;
//  Dwg_Data dwg;
//
//  dwg.num_objects = 0;
//  success = dwg_read_file("www/Villa.dwg", &dwg);
//  for (i = 0; i < dwg.num_objects; i++)
//    {
//      Dwg_Entity_LINE *line;
//      Dwg_Entity_CIRCLE *circle;
//      Dwg_Entity_TEXT *text;
//
//      switch (dwg.object[i].type)
//        {
//      case DWG_TYPE_LINE:
//        line = dwg.object[i].tio.entity->tio.LINE;
////        add_line(line->start.x, line->end.x, line->start.y, line->end.y);
//        break;
//      case DWG_TYPE_CIRCLE:
//        circle = dwg.object[i].tio.entity->tio.CIRCLE;
////        add_circle(circle->center.x, circle->center.y, circle->radius);
//        break;
//      case DWG_TYPE_TEXT:
//        text = dwg.object[i].tio.entity->tio.TEXT;
////        add_text(text->insertion_pt.x, text->insertion_pt.y, text->text_value);
//        break;
//        }
//    }
//  dwg_free(&dwg);
//  return success;
//  return 0;


  core::gLogManager.registerDisplay(boost::shared_ptr<core::IDisplay>
    (new core::COutDisplay(core::LogManager::eDebug)));

  libredwg2::Archive parser;
  const std::string strFile = "files/patrick.dwg";
  boost::shared_ptr<libredwg2::Schema> ptrSchema;
//  LOG_DEBUG(parser.restore("www/Villa.dwg", ptrSchema));
//  LOG_DEBUG(parser.restore("files/Villa2000.dwg", ptrSchema));
  core::ResultCode rc = parser.restore(strFile, ptrSchema);
  LOG_DEBUG(rc);
  if (rc.isFailure())
    return rc.getValue();
//  LOG_DEBUG(parser.restore("libredwg/examples/example.dwg", ptrSchema));

  if (ptrSchema == NULL)
    return -1;

  LOG_DEBUG(ptrSchema->getFaces3d().size());

  return 0;
}
