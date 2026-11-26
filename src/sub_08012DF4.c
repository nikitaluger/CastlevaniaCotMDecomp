struct GameState { u8 _0x000[0x18A8]; u8 roomIndex18A8; };
extern struct GameState gMainWorkspace;
struct CurrentRoom { volatile u8 roomIndex; };
extern struct CurrentRoom D_02027898;
extern u8 D_02023130[];
extern u8 D_080CB278[];
extern s32 getTileTerrain(s32, s32, s32);
extern s32 sub_080C364C(s32, s32);

/* Traces a fixed-point line from (x0,y0) by (dx,dy), sampling tiles along the way;
 * returns 1 when a tile matching the collision mask is hit (reporting the last
 * free position) and 0 when the whole segment is clear (reporting the endpoint). */
s32 sub_08012DF4(s32 x0, s32 y0, s32 dx, s32 dy, s32 *outX, s32 *outY, s32 tileMask)
{
  s32 mask = (u16) tileMask;
  s32 endX;
  s32 span;
  s32 tmp;
  s32 majorAbs;
  s32 minorAbs;
  s32 stepX;
  volatile u8 *roomIndex;
  s32 stepY;
  s32 step;
  s32 offsetX;
  s32 offsetY;
  s32 tileCode;
  tileCode = getTileTerrain(D_02023130 + (gMainWorkspace.roomIndex18A8 * 0x40), x0, y0);
  {
    u8 *collisionMaskTable = D_080CB278;
    if ((*((u16 *) (collisionMaskTable + (((u32) (tileCode << 0x10)) >> 0xF)))) & mask)
    {
      *outX = x0;
      *outY = y0;
      return 1;
    }
  }
  tmp = x0 + dx;
  endX = tmp;
  roomIndex = &D_02027898.roomIndex;
  span = y0 + dy;
  if (((x0 & 0xFFFF0000) == (tmp & 0xFFFF0000)) && ((y0 & 0xFFFF0000) == (span & 0xFFFF0000)))
  {
    *outX = tmp;
    *outY = span;
    return 0;
  }
  majorAbs = dx;
  if (dx < 0)
  {
    majorAbs = 0 - dx;
  }
  minorAbs = dy;
  if (dy < 0)
  {
    minorAbs = 0;
    minorAbs = minorAbs - dy;
  }
  if (majorAbs > minorAbs)
  {
    majorAbs = dx;
    if (dx < 0)
    {
      majorAbs = dx + 0xFFFF;
    }
  }
  else
  {
    majorAbs = dy;
    if (dy < 0)
    {
      majorAbs = dy + 0xFFFF;
    }
  }
  tmp = majorAbs >> 16;
  minorAbs = tmp;
  if (tmp < 0)
  {
    minorAbs = 0 - tmp;
  }
  tmp = minorAbs + 1;
  stepX = sub_080C364C(dx, tmp);
  stepY = sub_080C364C(dy, tmp);
  step = 1;
  if (step > tmp)
  {
    goto loopend;
  }
  offsetY = stepY;
  offsetX = stepX;
  do
  {
    s32 sampleX;
    s32 sampleY;
    if (step != tmp)
    {
      sampleX = x0 + offsetX;
      sampleY = y0 + offsetY;
    }
    else
    {
      sampleX = endX;
      sampleY = span;
    }
    tileCode = getTileTerrain(D_02023130 + ((*roomIndex) * 0x40), sampleX, sampleY);
    {
      u8 *collisionMaskTable = D_080CB278;
      if ((*((u16 *) (collisionMaskTable + (((u32) (tileCode << 0x10)) >> 0xF)))) & mask)
      {
        s32 prevStep = step - 1;
        *outX = (((stepX * prevStep) + x0) & 0xFFFF0000) + 0x8000;
        *outY = ((y0 + (stepY * prevStep)) & 0xFFFF0000) + 0x8000;
        return 1;
      }
    }
    offsetY += stepY;
    offsetX += stepX;
    step++;
  }
  while (step <= tmp);
  loopend:
  *outX = endX;

  *outY = span;
  return 0;
}
