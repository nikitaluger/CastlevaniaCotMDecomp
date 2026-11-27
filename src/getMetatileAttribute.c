/* Return the metatile attribute byte at the 16.16 map position (x, y), or -1
 * when the position is outside the map or its attribute data is missing. */
s32 getMetatileAttribute(u8 *map, s32 x, s32 y)
{
  s32 attrBase;
  s32 subX;
  s32 tileX;
  s32 width;
  u8 *mapPtr;
  s32 subY;
  s32 tileY;
  s32 height;
  s32 *widthPtr;
  u16 *row;
  u16 tile;
  s32 yOff;
  s32 tileOff;
  s32 rowOff;
  u8 *rowTable;
  s32 xOff;
  mapPtr = map;
  attrBase = *((s32 *) (map + 8));
  if (attrBase == 0)
  {
    goto ret_neg;
  }
  subX = x >> 19;
  widthPtr = &width;
  tileX = x >> 21;
  if (tileX < 0)
  {
    goto ret_neg;
  }
  width = *((s16 *) (mapPtr + 0x10));
  if ((*widthPtr) <= tileX)
  {
    goto ret_neg;
  }
  subY = y >> 19;
  tileY = y;
  tileY = tileY >> 21;
  if (tileY < 0)
  {
    goto ret_neg;
  }
  height = *((s16 *) (map + 0x12));
  if (height > tileY)
  {
    goto success;
  }
  ret_neg:
  return -1;

  success:
  rowOff = (tileY * width) * 2;
  rowTable = *((u8 **) (map + 0x0C));
  row = (u16 *) (rowTable + rowOff);
  xOff = tileX * 2;
  tile = *((u16 *)((u8 *)row + xOff));
  subY &= 3;
  subX &= 3;
  yOff = subY << 2;
  tileOff = tile << 4;
  return *((u8 *)(yOff + (tileOff + (u32)attrBase) + subX));
}
