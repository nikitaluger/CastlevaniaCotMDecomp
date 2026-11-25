extern u32 sub_080C3824(u32, u32);
extern u16 D_080C4290[];
s32 sub_08005910(s32 a, s32 b)
{
  s32 r2;
  int new_var;
  s32 r1;
  if ((b == 0) && (a == 0))
  {
    return 0;
  }
  r2 = (b < 0) ? (-b) : (b);
  new_var = a < 0;
  r1 = (new_var) ? (-a) : (a);
  if (((u32) r2) < ((u32) r1))
  {
    u32 mask;
    while (r2 & 0xFF800000)
    {
      r2 = ((u32) r2) >> 1;
      r1 = ((u32) r1) >> 1;
    }

    if (r1 == 0)
    {
      return (b >> 31) & 0x8000;
    }
    {
      u32 table = (u32) D_080C4290;
      u32 q = sub_080C3824(r2 << 9, r1);
      r1 = 0x4000 - (*((u16 *) (table + (q * 2))));
    }
  }
  else
  {
    u32 mask = 0xFF800000;
    while (r1 & mask)
    {
      r2 = ((u32) r2) >> 1;
      r1 = ((u32) r1) >> 1;
    }

    if (r2 == 0)
    {
      return (a < 0) ? (0xC000) : (0x4000);
    }
    {
      u32 table = (u32) D_080C4290;
      u32 q = sub_080C3824(r1 << 9, r2);
      r1 = *((u16 *) (table + (q * 2)));
    }
  }
  if (a < 0)
  {
    if (b < 0)
    {
      return r1 + 0x8000;
    }
    return 0x10000 - r1;
  }
  if (b < 0)
  {
    return 0x8000 - r1;
  }
  return r1;
}

