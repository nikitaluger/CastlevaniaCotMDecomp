struct S02025FF0
{
  u8 pad0[0x24];
  u32 f24;
  u8 pad28[0x02];
  u16 f2A;
  u8 pad2C[0x14C1];
  u8 f14ED;
  u8 pad14EE[0x23A];
  u32 f1728;
  u32 f172C;
  u8 pad1730[8];
  u16 f1738;
};
extern struct S02025FF0 D_02025FF0;
extern u8 D_02025368[];
extern u8 D_02021E90[];
extern u8 D_080E4E54[];
extern u8 D_080E47E8[];
extern u8 D_084E25C0[];
extern u8 D_084E25D4[];
s32 sub_08003740(void *, void *);
void sub_08003A6C(void *, u32, u32);
void *sub_0806D2A0(u32, u32, u32, u32);
s32 sub_0806D35C(void *, void *, void *);
void sub_0806D588(void *, void *);
void sub_0808DC40(s32, s32, u32);
void sub_080C31E0(u32, u32);
inline u8 *inline_fn(u8 *arg0)
{
  return arg0;
}

void sub_0807BD78(void *arg0)
{
  u8 *s = (u8 *) arg0;
  u8 *p4 = *((u8 **) (s + 0x6C));
  u8 *p8 = p4 + 4;
  int new_var5;
  u8 *new_var;
  u8 *v38 = *((u8 **) (s + 0x38));
  u32 new_var2;
  unsigned int new_var8;
  u8 *p5 = p8;
  u8 *new_var7;
  u8 *new_var3;
  u32 *new_var6;
  u8 *g = D_02025368;
  u8 *r6;
  u8 *new_var4;
  u8 *dEnd;
  s32 idx;
  s32 delta;
  s32 timer;
  void *other;
  if (sub_0806D35C(s, v38, p5) != 0)
  {
    return;
  }
  new_var7 = p5 + 0x10;
  timer = ++(*((s32 *) new_var7));
  new_var4 = D_080E4E54;
  idx = ((timer >> 6) & 0xF) * 8;
  delta = *((s32 *) (new_var4 + idx));
  if (D_02025FF0.f1738 & 0x10)
  {
    delta = -delta;
  }
  timer = ((*((s32 *) (&D_02025FF0.f1728))) + delta) - (*((s32 *) (p4 + 4)));
  if (timer < 0)
  {
    timer += 31;
  }
  *((s32 *) (p4 + 4)) = (*((s32 *) (p4 + 4))) + (timer >> 5);
  timer = ((*((s32 *) (&D_02025FF0.f172C))) + (*((s32 *) ((D_080E4E54 + 4) + idx)))) - (*((s32 *) (p5 + 4)));
  if (timer < 0)
  {
    timer += 31;
  }
  *((s32 *) (p5 + 4)) += timer >> 5;
  new_var = p8 + 0x1C;
  new_var8 = 0x10;
  if (D_02025FF0.f24 != 0)
  {
    if (D_02025FF0.f2A & (*((u16 *) (D_02025368 + 0x3BC))))
    {
      r6 = new_var;
      if (0 != (*((u32 *) (p8 + 0x54))))
      {
        goto dec;
      }
      sub_08003A6C(r6, 0, (u32) D_084E25D4);
      *((u32 *) (p8 + 0x54)) = 0x20;
    }
    else
    {
      r6 = p4 + 0x20;
    }
  }
  else
  {
    new_var5 = 0x146E;
    if ((*((u16 *) (D_02021E90 + new_var5))) & (*((u16 *) (g + 0x3BC))))
    {
      r6 = p8 + 0x1C;
      if ((*((u32 *) (p8 + 0x54))) != 0)
      {
        goto dec;
      }
      sub_08003A6C(r6, 0, (u32) D_084E25D4);
      *((u32 *) (p8 + 0x54)) = 0x20;
    }
    else
    {
      r6 = p4 + 0x20;
    }
  }
  if ((*((u32 *) (p8 + 0x54))) == 0)
  {
    goto skip;
  }
  new_var3 = (u8 *) (&D_02025FF0);
  dec:
  timer = (*((u32 *) (p8 + 0x54))) - 1;

  *((u32 *) (p8 + 0x54)) = timer;
  if (timer == 0x18)
  {
    other = sub_0806D2A0(*((u32 *) (s + 0x28)), 0x54, 0x0A, 0x12);
    new_var6 = &(*((u32 *) p5));
    if (other != NULL)
    {
      *((u32 *) (((u8 *) other) + 0x7C)) = *new_var6;
      *((u32 *) inline_fn(((u8 *) other) + 0x8C)) = *((u32 *) (p5 + 4));
      timer = (((*((u8 *) (g + 0x304))) - 1) * 12) + ((idx = (*((u8 *) (g + 0x305))) - 1) * 120);
      *((u32 *) (D_02025368 + 0x2CC)) -= *((u32 *) ((D_080E47E8 + 4) + timer));
    }
  }
  skip:
  dEnd = new_var3;

  if ((*((s32 *) p5)) > (*((s32 *) (dEnd + 0x1728))))
  {
    *((u16 *) (v38 + 2)) |= new_var8;
  }
  else
  {
    *((u16 *) (v38 + 2)) &= 0xFFEF;
  }
  if (sub_08003740(r6, v38) == 0)
  {
    sub_08003A6C(r6, 0, (u32) D_084E25C0);
  }
  new_var2 = (u32) s;
  sub_0806D588(v38, p5);
  if ((*((u8 *) (dEnd + 0x14ED))) == 0x81)
  {
    return;
  }
  sub_0808DC40(*((s32 *) p5), *((s32 *) (p5 + 4)), 0);
  sub_080C31E0(new_var2, *((u32 *) (s + 0x24)));
}
