struct S_02025FF0
{
  u8 _0x000[0x18A8];
  u8 cameraIndex;
};
extern struct S_02025FF0 gMainWorkspace;
extern u8 gTilemapPages[];
/* Return 1 when the world point (x,y) lies inside the active camera rectangle,
 * whose half-extents come from the record gTilemapPages[cameraIndex << 6] at +0x10/+0x12.
 * The four 16.16 margins inset each side; 0 when the point is outside. */
s32 sub_08015850(s32 x, s32 y, u16 xUpperMargin, s32 xLowerMargin, u16 yUpperMargin, u16 yLowerMargin)
{
  u16 xUpper = xUpperMargin;
  u16 yLowerTmp = yUpperMargin;
  u16 yLower = yLowerMargin;
  u8 recordIndex = gMainWorkspace.cameraIndex;
  u8 *record = gTilemapPages + (recordIndex << 6);
  s16 xExtent = *((s16 *) (record + 0x10));
  s16 yExtent = *((s16 *) (record + 0x12));
  s32 xBound = ((s32) xExtent) << 21;
  s32 yBound = ((s32) yExtent) << 21;
  s32 xAdjusted = x + (xLowerMargin << 16);
  if (xAdjusted < 0)
  {
    return 0;
  }
  if ((x + (xUpper << 16)) > xBound)
  {
    return 0;
  }
  if ((y + (yLower << 16)) < 0)
  {
    return 0;
  }
  if ((y + (yLowerTmp << 16)) > yBound)
  {
    return 0;
  }
  if (x)
  {
    return 1;
  }
  else
  {
    return 1;
  }
}
