struct P_0806
{
  u8 _0[0x18];
  s32 f18;
  s32 f1C;
  u8 _20[0x20];
};
struct Arg1_0806
{
  s32 f0;
  s32 f4;
};
struct Flags_0806
{
  u8 f0;
  u8 f1;
  u8 f2;
  u8 f3;
};
struct Big_0806
{
  u8 _0[0x1754];
  s32 f1754;
  u8 _1758[0x18];
  s32 f1770;
  s32 f1774;
  s32 f1778;
  s32 f177C;
  u8 _1780[0x18A8 - 0x1780];
  u8 f18A8;
  s32 f18AC;
  struct Flags_0806 f18B0[1];
};
extern struct Big_0806 D_02025FF0;
extern struct P_0806 D_02023130[];
void sub_0806A884(s32 *arg0, struct Arg1_0806 *arg1)
{
  u8 idx = D_02025FF0.f18A8;
  struct P_0806 *p = &D_02023130[idx];
  struct Flags_0806 *fl = &D_02025FF0.f18B0[idx];
  unsigned short new_var;
  u8 *p1774;
  s32 t1;
  s32 t2;
  s32 tmp;
  s32 k1 = 0xF0 << 15;
  s32 k2 = 0xE0 << 15;
  if (!(fl->f0 & 0x80))
  {
    if (fl->f0 & 0x40)
    {
      t1 = (arg1->f0 & 0xFFFF0000) - (p->f18 + k1);
      if (t1 < 0)
      {
        t1 += 3;
      }
      t1 >>= 2;
      t2 = (arg1->f4 & 0xFFFF0000) - (p->f1C + k2);
      if (t2 < 0)
      {
        t2 += 3;
      }
      t2 >>= 2;
      p->f18 += t1;
      p->f1C += t2;
    }
    else
    {
      p->f18 = (arg1->f0 & 0xFFFF0000) + 0xFF880000;
      p->f1C = (arg1->f4 & 0xFFFF0000) + 0xFF900000;
    }
  }
  tmp = fl->f0 & 1;
  if (tmp)
  {
    s32 mn;
    if (p->f18 < 0)
    {
      p->f18 = 0;
    }
    mn = (fl->f1 << 24) + 0xFF100000;
    if (p->f18 > mn)
    {
      p->f18 = mn;
    }
  }
  else
  {
    p->f18 = tmp;
  }
  {
    u8 f2 = fl->f0 & 2;
    if (f2)
    {
      s32 mn;
      if (p->f1C < 0)
      {
        p->f1C = 0;
      }
      mn = (fl->f2 << 24) + 0xFF5E0000;
      if (p->f1C > mn)
      {
        p->f1C = mn;
      }
    }
    else
    {
      p->f1C = f2;
    }
  }
  if (D_02025FF0.f1754)
  {
    p->f1C += (D_02025FF0.f1754 & 2) << 16;
    D_02025FF0.f1754 -= 1;
  }
  arg0[5] = (arg1->f0 & 0xFFFF0000) - p->f18;
  arg0[6] = (arg1->f4 & 0xFFFF0000) - p->f1C;
  D_02025FF0.f1770 = p->f18;
  p1774 = (u8 *) (&D_02025FF0.f1774);
  *((s32 *) p1774) = p->f1C;
  {
    u8 other = D_02025FF0.f18A8 ^ 1;
    struct P_0806 *p2 = &D_02023130[other];
    struct Flags_0806 *fl2 = &D_02025FF0.f18B0[other];
    new_var = p->f18;
    if (!(fl2->f0 & 0x80))
    {
      s32 sh = new_var >> 16;
      p2->f18 = D_02025FF0.f18AC * sh;
      p2->f1C = D_02025FF0.f18AC * (*((s16 *) (p1774 + 2)));
      if (!(fl2->f0 & 1))
      {
        p2->f18 = 0;
      }
      {
        u8 f2 = fl2->f0 & 2;
        if (!f2)
        {
          p2->f1C = f2;
        }
      }
      D_02025FF0.f1778 = p2->f18;
      D_02025FF0.f177C = p2->f1C;
    }
  }
}

