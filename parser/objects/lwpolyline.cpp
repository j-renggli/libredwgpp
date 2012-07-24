#include "lwpolyline.h"

#include "../version.h"

namespace libredwgpp {

namespace parserobject {

////////////////////////////////////////////////////////////////

// P. 112
core::ResultCode PolyLine::restoreFull(ISchema& schema, DWGBuffer& buffer, const Colour& colour, const Handle& handle, const Version& version) const
{
  double xeco = 0.;
  double xo = 0.;
  double co = 0.;
  uint16_t index = buffer.readBit16();
  if (index & 0x04) {
    xeco = buffer.readBitDouble();
  }
  if (index & 0x08) {
    xo = buffer.readBitDouble();
  }
  if (index & 0x02) {
    co = buffer.readBitDouble();
  }
  double x = 0;
  double y = 0;
  double z = 0;
  if (index & 0x01) {
    x = buffer.readBitDouble();
    y = buffer.readBitDouble();
    z = buffer.readBitDouble();
    LOG_DEBUG("A");
  }
    LOG_DEBUG("LWPOLYLINE [" << x << ", " << y << ", " << z << "]");

  uint32_t vertical = buffer.readBit32();
  LOG_DEBUG(vertical);

  uint32_t round = 0;
  if (index & 0x10) {
    round = buffer.readBit32();
    LOG_DEBUG(round);
  }

//return core::rcFailure;
////unsigned i;
////1285 	  	         Dvg_Estajxo_LWPOLYLINE *est;
////obj->supertipo = DVG_OST_ESTAJXO;
////obj->tio.estajxo = malloc (sizeof (Dvg_Objekto_Estajxo));
////obj->tio.estajxo->tio.LWPOLYLINE = calloc (sizeof (Dvg_Estajxo_LWPOLYLINE), 1);
//dvg_dek_estajxo (dat, obj->tio.estajxo);
////est = obj->tio.estajxo->tio.LWPOLYLINE;
///* Legitaj valoroj*/
////est->indikiloj = bit_legi_BS (dat);
////if (est->indikiloj & 0x0004)
////1297 	  	                 est->largxeco = bit_legi_BD (dat);
////1298 	  	         else
////1299 	  	                 est->largxeco = 0;
////1300 	  	         if (est->indikiloj & 0x0008)
////1301 	  	                 est->levigxo = bit_legi_BD (dat);
////1302 	  	         else
////1303 	  	                 est->levigxo = 0;
////1304 	  	         if (est->indikiloj & 0x0002)
////1305 	  	                 est->dikeco = bit_legi_BD (dat);
////1306 	  	         else
////1307 	  	                 est->dikeco = 0;
////1308 	  	         if (est->indikiloj & 0x0001)
////1309 	  	         {
////1310 	  	                 est->forpusxigo.x = bit_legi_BD (dat);
////1311 	  	                 est->forpusxigo.y = bit_legi_BD (dat);
////1312 	  	                 est->forpusxigo.z = bit_legi_BD (dat);
////1313 	  	         }
////1314 	  	         else
////1315 	  	                 est->forpusxigo.x = est->forpusxigo.y = est->forpusxigo.z = 0;
//1316
//1317 	  	         est->vertico_kiom = bit_legi_BL (dat);
//1318
//1319 	  	         if (est->indikiloj & 0x0010)
//1320 	  	                 est->rondigo_kiom = bit_legi_BL (dat);
//1321 	  	         else
//1322 	  	                 est->rondigo_kiom = 0;
//1323
//1324 	  	         if (est->indikiloj & 0x0020)
//1325 	  	                 est->linilargxo_kiom = bit_legi_BL (dat);
//1326 	  	         else
//1327 	  	                 est->linilargxo_kiom = 0;
//1328
//1329 	  	         est->vertico = malloc (est->vertico_kiom * sizeof (Punkto_2D));
//1330 	  	         est->vertico[0].x = bit_legi_RD (dat);
//1331 	  	         est->vertico[0].y = bit_legi_RD (dat);
//1332 	  	         for (i = 1; i < est->vertico_kiom; i++)
//1333 	  	         {
//1334 	  	                 est->vertico[i].x = bit_legi_DD (dat, est->vertico[i - 1].x);
//1335 	  	                 est->vertico[i].y = bit_legi_DD (dat, est->vertico[i - 1].y);
//1336 	  	         }
//1337
//1338 	  	         if (est->rondigo_kiom > 0)
//1339 	  	         {
//1340 	  	                 est->rondigo = malloc (est->rondigo_kiom * sizeof (double));
//1341 	  	                 for (i = 0; i < est->rondigo_kiom; i++)
//1342 	  	                         est->rondigo[i] = bit_legi_BD (dat);
//1343 	  	         }
//1344
//1345 	  	         if (est->linilargxo_kiom > 0)
//1346 	  	         {
//1347 	  	                 est->linilargxo = malloc (est->linilargxo_kiom * sizeof (Punkto_2D));
//1348 	  	                 for (i = 0; i < est->linilargxo_kiom; i++)
//1349 	  	                 {
//1350 	  	                         est->linilargxo[i].ek = bit_legi_BD (dat);
//1351 	  	                         est->linilargxo[i].fin = bit_legi_BD (dat);
//1352 	  	                 }
//1353 	  	         }
//1354
//1355 	         dvg_dek_traktref (dat, obj); 	         dvg_dek_traktref (dat, obj);
//
//
//
//  UnicodeString strShapeFileName = buffer.readText(version);
////  LOG_DEBUG(strShapeFileName);
///*  bool flag64 = */buffer.readBit();
////  LOG_DEBUG(flag64);
///*  int xrefindex = */buffer.readBit16();// - 1;
////  LOG_DEBUG(xrefindex);
////  if (xrefindex >= 0)
////  {
////    bool xdep = buffer.readBit();
////    LOG_DEBUG(xdep);
////  }
////  bool isVertical = buffer.readBit();
////  LOG_DEBUG(isVertical);
////  bool isShapeFile = buffer.readBit();
////  LOG_DEBUG(isShapeFile);
////  double fixedHeight = buffer.readBitDouble();
////  LOG_DEBUG(fixedHeight);
////  double widthFactor = buffer.readBitDouble();
////  LOG_DEBUG(widthFactor);
////  double oblique = buffer.readBitDouble();
////  LOG_DEBUG(oblique);
////  size_t genFlags = buffer.readRaw8();
////  LOG_DEBUG(genFlags);
////  double lastHeight = buffer.readBitDouble();
////  LOG_DEBUG(lastHeight);

  return core::rcSuccess;
}

////////////////////////////////////////////////////////////////

}

}
