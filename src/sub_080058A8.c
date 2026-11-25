/* 16.16 fixed-point multiply: returns (valueA * valueB) >> shift, where shift
 * is chosen so the 32-bit product does not overflow; when the operands are too
 * precise the one with the higher magnitude is pre-shifted right bit by bit. */
s32 sub_080058A8(s32 valueA, s32 valueB)
{
  s32 x;
  s32 shift;
  s32 totalBits;
  s32 maskX;
  s32 maskY;
  s32 y;
  s32 shiftY;
  s32 shiftX;
  y = valueB;
  x = valueA;
  totalBits = 0x30;
  if ((x == 0) || (y == 0))
  {
    return 0;
  }
  shiftX = 0;
  shiftY = 0;
  maskX = 0x80000000;
  if (x >= 0)
  {
    do
    {
      shiftX += 1;
      maskX = maskX >> 1;
    }
    while (!(maskX & x));
  }
  maskY = 0x80000000;
  if (y >= 0)
  {
    do
    {
      shiftY += 1;
      maskY = maskY >> 1;
    }
    while (!(maskY & y));
  }
  shift = (totalBits - shiftY) - shiftX;
  if (shift > 0xF)
  {
    do
    {
      if (shiftX < shiftY)
      {
        x = x >> 1;
        shiftX += 1;
      }
      else
      {
        y = y >> 1;
        shiftY += 1;
      }
      shift -= 1;
    }
    while (shift > 0xF);
  }
  return ((s32) (x * y)) >> shift;
}
