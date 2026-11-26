struct B479C
{
  u16 f00;
  u16 f02;
  u32 f04;
  u32 f08;
  u16 *f0C;
  s16 f10;
  s16 f12;
  u8 pad_14[0x0C];
  s16 f20;
  s16 f22;
  u8 pad_24[0x18];
  u16 f3C;
  u16 f3E;
};
extern void sub_08004484(struct B479C *a, s32 b, s32 c, s32 d, s32 e);
extern void sub_080C2EC8(u8 *ptr, s32 a, s32 b);
inline static s32 inline_fn(s32 *arg0)
{
  return arg0[0];
}

void sub_0800479C(struct B479C *a, s32 b, s32 c, u16 d)
{
  s32 sentinel_const0 = 1;
  s32 sentinel_const1 = 1;
  s32 sp04[4];
  s32 sp14[4];
  s32 sp24[4];
  s32 sp34[4];
  u8 flags[4];
  s32 *pD;
  s32 *pB;
  s32 i;
  s32 tileX1;
  s32 tileY1;
  s32 tileX0;
  s32 tileY0;
  u16 temp;
  sub_080C2EC8(flags, 0, 4);
  flags[0] = 1;
  {
    u16 *p = a->f0C;
    p += b;
    p += c * a->f10;
    *p = d;
  }
  do
  {
    tileY0 = b << 2;
  }
  while (0);
  tileX0 = c << 2;
  tileY1 = tileY0 + 3;
  tileX1 = tileX0; tileX1 += 3;
  sp04[0] = ((s16) a->f3C) >> 3;
  sp14[0] = ((s16) a->f3E) >> 3;
  sp24[0] = ((((s16) a->f3C) + ((s16) a->f20)) - 1) >> 3;
  sp34[0] = ((((s16) a->f3E) + ((s16) a->f22)) - 1) >> 3;
  do
  {
    temp = a->f00;
    if (temp & 0x400)
    {
      if (inline_fn(sp04) < 0)
      {
        do
        {
          sp04[0] += a->f10 << 2;
          sp24[0] += a->f10 << 2;
        }
        while (inline_fn(sp04) < 0);
      }
      else
      {
        s16 t = a->f10;
        s32 v = t << 2;
        if (inline_fn(sp04) >= v)
        {
          do
          {
            sp04[0] -= t << 2;
            do
            {
              sp24[0] -= v;
            }
            while (0);
          }
          while (inline_fn(sp04) >= v);
        }
      }
    }
  }
  while (0);
  if (a->f00 & 0x200)
  {
    if (inline_fn(sp14) < 0)
    {
      do
      {
        sp14[0] += a->f12 << 2;
        sp34[0] += a->f12 << 2;
      }
      while (inline_fn(sp14) < 0);
    }
    else
    {
      s16 t = a->f12;
      s32 v = t << 2;
      if (inline_fn(sp14) >= v)
      {
        do
        {
          sp14[0] -= v;
          do
          {
            sp34[0] -= v;
          }
          while (0);
        }
        while (inline_fn(sp14) >= v);
      }
    }
  }
  if (a->f00 & 0x400)
  {
    s16 t = a->f10;
    s32 v = t << 2;
    if (inline_fn(sp24) >= v)
    {
      sp04[1] = 0;
      sp24[1] = inline_fn(sp24) - v;
      sp24[0] = v - 1;
      flags[1] = 1;
    }
  }
  if (a->f00 & 0x200)
  {
    s16 t = a->f12;
    s32 v = t << 2;
    if (inline_fn(sp34) >= v)
    {
      sp14[2] = 0;
      sp34[2] = inline_fn(sp34) - v;
      sp34[0] = v - 1;
      flags[2] = 1;
    }
  }
  sp14[1] = inline_fn(sp14);
  sp34[1] = inline_fn(sp34);
  sp04[2] = inline_fn(sp04);
  sp24[2] = inline_fn(sp24);
  if (flags[1] == sentinel_const0)
  {
    if (flags[2] == sentinel_const1)
    {
      flags[3] = flags[2];
      sp04[3] = sp04[1];
      sp24[3] = sp24[1];
      sp14[3] = sp14[2];
      sp34[3] = sp34[2];
    }
  }
  pD = sp34;
  pB = sp14;
  for (i = 0; i < 4; i++)
  {
    if (flags[i] == sentinel_const0)
    {
      s32 ty0 = tileY0;
      s32 tx0 = tileX0;
      s32 ty1 = tileY1;
      s32 tx1 = tileX1;
      s32 *pC = &sp24[i];
      s32 *pA = &sp04[i];
      if ((((ty1 >= (*pA)) && (ty0 <= (*pC))) && (tx1 >= inline_fn(pB))) && (tx0 <= inline_fn(pD)))
      {
        if (ty0 < (*pA))
        {
          ty0 = *pA;
        }
        if (ty1 > (*pC))
        {
          ty1 = *pC;
        }
        if (tx0 < inline_fn(pB))
        {
          tx0 = inline_fn(pB);
        }
        if (tx1 > inline_fn(pD))
        {
          tx1 = inline_fn(pD);
        }
        sub_08004484(a, ty0, tx0, ty1, tx1);
      }
    }
    pD++;
    pB++;
  }

}

