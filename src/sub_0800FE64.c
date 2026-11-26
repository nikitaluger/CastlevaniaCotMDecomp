extern s32 divideInt(s32, s32);
extern s32 moduloInt(s32, s32);

/* Write the decimal digits of a value right-aligned into a u16 tile map of
 * digitCount tiles. Each digit is (tileBase + digit) & 0x3FF with the palette
 * in the high bits; leading zeros past the first written digit are blanked. */
void sub_0800FE64(s32 initialValue, s32 paletteValue, s32 digitCount, s32 tileOffset, u16 *destBuf)
{
  s32 value;
  s32 digitsLeft;
  u16 *dst;
  u8 palette;
  u16 tileBase;
  s32 notFirst;
  value = initialValue;
  digitsLeft = digitCount;
  dst = destBuf;
  palette = paletteValue;
  tileBase = tileOffset;
  notFirst = 0;
  while (digitsLeft != 0)
  {
    s32 digit;
    digit = moduloInt(value, 10);
    value = divideInt(value, 10);
 do { if (((notFirst == 0) || (value != 0)) || (digit != 0)) { *dst = ((tileBase + digit) & 0x3FF) | (palette << 12); } else { *dst = (u16) digit; } dst--; digitsLeft--; notFirst = 1; } while (0);
  }
}
