/* Field at 0x18A8 of the workspace selects the active 0x40-byte tile-map page. */
struct CollisionWorkspace {
  u8 _0x000[0x18A8];
  u8 mapIndex;
};
extern struct CollisionWorkspace gMainWorkspace;

/* Live map index: volatile because a sweep can cross into another page. */
struct LiveMapState {
  volatile u8 index;
};
extern struct LiveMapState gLiveMapIndex;
extern u8 gTilemapPages[];
extern u8 gTileTerrainFlagsB[];
extern s32 getTileTerrainB(s32, s32, s32);
extern s32 divInt32(s32, s32);

/*
 * Sweep the 16.16 vector (deltaX, deltaY) from (startX, startY), sampling the
 * alternate tile map at every step. Returns 1 with the centre of the last free
 * tile when a tile matching tileMask blocks the path, or 0 with the target.
 */
s32 sweepTilemapCollision(s32 startX, s32 startY, s32 deltaX, s32 deltaY,
                          s32 *outX, s32 *outY, s32 tileMask)
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
  tileType = getTileTerrainB(gTilemapPages + (gMainWorkspace.mapIndex * TILEMAP_PAGE_STRIDE), startX, startY);
  {
    u8 *tileProps = gTileTerrainFlagsB;
    if ((*((u16 *) (tileProps + (((u32) (tileType << 0x10)) >> 0xF)))) & blockMask)
    {
      *outX = startX;
      *outY = startY;
      return 1;
    }
  }
  scratch = startX + deltaX;
  targetX = scratch;
  mapIndex = &gLiveMapIndex.index;
  targetY = startY + deltaY;
  if (((startX & FIXED_POINT_FRAC_MASK) == (scratch & FIXED_POINT_FRAC_MASK)) &&
      ((startY & FIXED_POINT_FRAC_MASK) == (targetY & FIXED_POINT_FRAC_MASK)))
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
      maxDelta = deltaX + FIXED_TRUNC_BIAS;
    }
  }
  else
  {
    maxDelta = deltaY;
    if (deltaY < 0)
    {
      maxDelta = deltaY + FIXED_TRUNC_BIAS;
    }
  }
  scratch = maxDelta >> 16;
  absDelta = scratch;
  if (scratch < 0)
  {
    absDelta = 0 - scratch;
  }
  scratch = absDelta + 1;
  stepX = divInt32(deltaX, scratch);
  stepY = divInt32(deltaY, scratch);
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
    tileType = getTileTerrainB(gTilemapPages + ((*mapIndex) * TILEMAP_PAGE_STRIDE), probeX, probeY);
    {
      u8 *tileProps = gTileTerrainFlagsB;
      if ((*((u16 *) (tileProps + (((u32) (tileType << 0x10)) >> 0xF)))) & blockMask)
      {
        s32 prevStep = step - 1;
        *outX = (((stepX * prevStep) + startX) & FIXED_POINT_FRAC_MASK) + TILE_CENTER_BIAS;
        *outY = ((startY + (stepY * prevStep)) & FIXED_POINT_FRAC_MASK) + TILE_CENTER_BIAS;
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
