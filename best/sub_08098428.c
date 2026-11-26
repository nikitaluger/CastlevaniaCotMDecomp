void sub_08098428(s32 arg0, s32 arg1)
{
  u16 *pA;
  u16 *pB;
  u32 bit;
  do { pA = (u16 *) 0x020213E0; } while (0);
  pB = pA + 0x40;
  bit = 1;
  do
  {
    if (bit == 0x10)
    {
      do { pA = (u16 *) 0x020214E0; } while (0);
      pB = pA + 0x40;
    }
    if (arg0 & bit)
    {
      u32 i;
      u32 m;
      u16 *a;
      u16 *b;
      i = 0;
      m = 0x1F;
      do { a = pA; } while (0);
      do { b = pB; } while (0);
      do
      {
        u16 v;
        u32 c;
        u32 lo;
        u32 mid;
        u32 hi;
        v = *b;
        c = v << 16;
        lo = v & 0x1F;
        mid = (c >> 21) & m;
        hi = (c >> 26) & m;
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
    do { pA = (u16 *) (((u8 *) pA) + 0x20); } while (0);
    do { pB = (u16 *) (((u8 *) pB) + 0x20); } while (0);
    bit <<= 1;
  }
  while (bit <= 0xFF);
}

