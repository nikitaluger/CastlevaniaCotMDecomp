extern s32 sub_08000E98(s32, s32, s32, s32, s32);

/* For each set bit of a 16-bit mask, copy a 0x20-byte palette block into
 * object or background PALRAM from the source selected by the mode nibble of
 * *modeField, then clear that consumed nibble. */
void sub_08098338(s32 mask, u16 *modeField)
{
  s32 srcStep;
  s32 srcStride;
  s32 objSrc;
  s32 bgSrc;
  s32 objPal;
  s32 bgPal;
  u32 mode;
  u32 objBit;
  u32 bgBit;

  mode = ((u16) (*modeField)) >> 0xC;
  if (mode == 8)
  {
    srcStep = 0x10;
    objSrc = 0x020213E0;
    bgSrc = 0x020214E0;
  }
  else
  {
    srcStep = 0;
    bgSrc = (mode << 5) + 0x05000200;
    objSrc = bgSrc;
  }
  objPal = 0x05000300;
  objBit = 1;
  srcStride = srcStep * 2;
  do
  {
    if (mask & objBit)
    {
      do { sub_08000E98(1, objSrc, objPal, 0x20, 0x10); } while (0);
    }
    objSrc += srcStride;
    objPal += 0x20;
    objBit *= 2;
  }
  while (0xFU >= objBit);
  bgPal = 0x05000180;
  bgBit = 0x10;
  do
  {
    if (mask & bgBit)
    {
      sub_08000E98(1, bgSrc, bgPal, 0x20, 0x10);
    }
    bgSrc += srcStride;
    bgPal += 0x20;
    bgBit *= 2;
  }
  while (bgBit <= 0xFFU);
  *modeField = 0xFFF & (*modeField);
}
