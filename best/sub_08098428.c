void sub_08098428(s32 arg0, s32 arg1)
{
  u16 *pA = (u16 *) 0x020213E0;
  u16 *pB = pA + 0x40;
  u32 bit = 1;
  do
  {
    if (bit == 0x10)
    {
      pA = (u16 *) 0x020214E0;
      pB = pA + 0x40;
    }
    if (arg0 & bit)
    {
      u32 i = 0;
      u32 m = 0x1F;
      u16 *a = pA;
      u16 *b = pB;
      do
      {
        u16 v = *b;
        u32 c = v << 16;
        u32 lo = v & 0x1F;
        u32 mid = (c >> 21) & m;
        u32 hi = (c >> 26) & m;
        lo = (lo * arg1) >> 16;
        mid = (mid * arg1) >> 16;
        hi = (hi * arg1) >> 16;
        *a = (lo | (mid << 5)) | (hi << 10);
        a++;
        b++;
        i++;
      }
      while (i <= 0x0F);
    }
    pA = (u16 *) (((u8 *) pA) + 0x20);
    pB = (u16 *) (((u8 *) pB) + 0x20);
    bit <<= 1;
  }
  while (bit <= 0xFF);
}

