/* Global room state: the byte at 0x18A8 selects which 0x40-byte tile map is in use. */
struct RoomState
{
  u8 _0[0x18A8];
  u8 roomIndex;
};
extern struct RoomState D_02025FF0;

/* Live map index: volatile because a sweep can cross into another map. */
struct LiveMapState
{
  volatile u8 mapIndex;
};
extern struct LiveMapState D_02027898;
extern u8 D_02023130[];
extern u8 D_080D0054[];
extern s32 sub_08007DD8(s32, s32, s32);
extern s32 sub_080C364C(s32, s32);

/*
 * Sweep a movement vector through the tile map. Returns 1 and the centre of the
 * last free tile when a blocking tile is hit, 0 and the target point otherwise.
 */
s32 sub_0805DC5C(s32 startX, s32 startY, s32 deltaX, s32 deltaY, s32 *outX, s32 *outY, s32 tileMask)
{
  s32 blockMask = (u16) tileMask;
  s32 targetX;
  s32 targetY;
  s32 scratch;
  s32 maxDelta;
  s32 absDelta;
  s32 stepX;
  volatile u8 *mapIndex;
  s32 stepY;
  s32 step;
  s32 offsetX;
  s32 offsetY;
  s32 tileType;
  tileType = sub_08007DD8(D_02023130 + (D_02025FF0.roomIndex * 0x40), startX, startY);
  {
    u8 *tileProps = D_080D0054;
    if ((*((u16 *) (tileProps + (((u32) (tileType << 0x10)) >> 0xF)))) & blockMask)
    {
      *outX = startX;
      *outY = startY;
      return 1;
    }
  }
  scratch = startX + deltaX;
  targetX = scratch;
  mapIndex = &D_02027898.mapIndex;
  targetY = startY + deltaY;
  if (((startX & 0xFFFF0000) == (scratch & 0xFFFF0000)) && ((startY & 0xFFFF0000) == (targetY & 0xFFFF0000)))
  {
    *outX = scratch;
    *outY = targetY;
    return 0;
  }
  maxDelta = deltaX;
  if (deltaX < 0)
  {
    maxDelta = 0 - deltaX;
  }
  absDelta = deltaY;
  if (deltaY < 0)
  {
    absDelta = 0;
    absDelta = absDelta - deltaY;
  }
  if (maxDelta > absDelta)
  {
    maxDelta = deltaX;
    if (deltaX < 0)
    {
      maxDelta = deltaX + 0xFFFF;
    }
  }
  else
  {
    maxDelta = deltaY;
    if (deltaY < 0)
    {
      maxDelta = deltaY + 0xFFFF;
    }
  }
  scratch = maxDelta >> 16;
  absDelta = scratch;
  if (scratch < 0)
  {
    absDelta = 0 - scratch;
  }
  scratch = absDelta + 1;
  stepX = sub_080C364C(deltaX, scratch);
  stepY = sub_080C364C(deltaY, scratch);
  step = 1;
  if (step > scratch)
  {
    goto loopend;
  }
  offsetY = stepY;
  offsetX = stepX;
  do
  {
    s32 probeX;
    s32 probeY;
    if (step != scratch)
    {
      probeX = startX + offsetX;
      probeY = startY + offsetY;
    }
    else
    {
      probeX = targetX;
      probeY = targetY;
    }
    tileType = sub_08007DD8(D_02023130 + ((*mapIndex) * 0x40), probeX, probeY);
    {
      u8 *tileProps = D_080D0054;
      if ((*((u16 *) (tileProps + (((u32) (tileType << 0x10)) >> 0xF)))) & blockMask)
      {
        s32 prevStep = step - 1;
        *outX = (((stepX * prevStep) + startX) & 0xFFFF0000) + 0x8000;
        *outY = ((startY + (stepY * prevStep)) & 0xFFFF0000) + 0x8000;
        return 1;
      }
    }
    offsetY += stepY;
    offsetX += stepX;
    step++;
  }
  while (step <= scratch);
  loopend:
  *outX = targetX;

  *outY = targetY;
  return 0;
}
