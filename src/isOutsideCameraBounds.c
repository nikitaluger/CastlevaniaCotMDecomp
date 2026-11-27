extern u8 gCameraState[];
extern u8 gMainWorkspace[];
inline int withMargin(s32 arg0)
{
  return arg0 + 0xFFBF0000;
}

/* Returns 1 when (worldX, worldY) lies outside the current camera view
 * rectangle (with fixed margins), 0 when it is inside. */
s32 isOutsideCameraBounds(s32 worldX, s32 worldY)
{
  u8 *coordTable = gCameraState;
  s32 recordOffset = (gMainWorkspace[0x18A8] + 1) << 6;
  u8 *xBase = coordTable + 0x1278;
  s32 originX = *((s32 *) (xBase + recordOffset));
  u8 *yBase = coordTable + 0x127C;
  s32 originY = *((s32 *) (yBase + recordOffset));
  s32 xMin = originX + 0xFFBF0000;
  s32 xMax = originX + 0x01310000;
  s32 yMin = withMargin(originY);
  s32 yMax = originY + 0x01210000;
  if ((((worldX < xMin) || (worldX > xMax)) || (worldY < yMin)) || (worldY > yMax))
  {
    return 1;
  }
  return 0;
}
