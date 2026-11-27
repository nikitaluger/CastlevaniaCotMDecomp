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
extern u8 gTileTerrainFlags[];
extern s32 getTileTerrain(s32, s32, s32);
extern s32 divInt32(s32, s32);

/*
 * Walk the 16.16 vector (deltaX, deltaY) from (startX, startY), sampling the tile
 * map at every step. Returns 1 with the centre of the last free tile when a tile
 * matching collisionMask blocks the path, or 0 with the target if it is clear.
 */
s32 traceTilemapCollision(s32 startX, s32 startY, s32 deltaX, s32 deltaY,
                          s32 *resultX, s32 *resultY, s32 collisionMask)
{
  s32 blockMask = (u16) collisionMask;
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
  s32 terrain;
  terrain = getTileTerrain(gTilemapPages + (gMainWorkspace.mapIndex * TILEMAP_PAGE_STRIDE), startX, startY);
  {
    u8 *tileFlags = gTileTerrainFlags;
    if ((*((u16 *) (tileFlags + (((u32) (terrain << 0x10)) >> 0xF)))) & blockMask)
    {
      *resultX = startX;
      *resultY = startY;
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
    *resultX = scratch;
    *resultY = targetY;
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
    s32 sampleX;
    s32 sampleY;
    if (step != scratch)
    {
      sampleX = startX + offsetX;
      sampleY = startY + offsetY;
    }
    else
    {
      sampleX = targetX;
      sampleY = targetY;
    }
    terrain = getTileTerrain(gTilemapPages + ((*mapIndex) * TILEMAP_PAGE_STRIDE), sampleX, sampleY);
    {
      u8 *tileFlags = gTileTerrainFlags;
      if ((*((u16 *) (tileFlags + (((u32) (terrain << 0x10)) >> 0xF)))) & blockMask)
      {
        s32 prevStep = step - 1;
        *resultX = (((stepX * prevStep) + startX) & FIXED_POINT_FRAC_MASK) + TILE_CENTER_BIAS;
        *resultY = ((startY + (stepY * prevStep)) & FIXED_POINT_FRAC_MASK) + TILE_CENTER_BIAS;
        return 1;
      }
    }
    offsetY += stepY;
    offsetX += stepX;
    step++;
  }
  while (step <= scratch);
  loopend:
  *resultX = targetX;

  *resultY = targetY;
  return 0;
}
