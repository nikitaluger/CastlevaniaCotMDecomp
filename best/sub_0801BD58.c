s32 sub_08014990(s32);
void *sub_08016238(void);
void sub_0808E9AC(s32, s32, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
s32 sub_0801BD58(void *arg0)
{
  void *p38;
  void *p3C;
  u8 *r6;
  u32 *new_var4;
  s32 result;
  void *r4;
  s32 cur;
  s32 off;
  s32 addr;
  s32 val;
  u8 *base;
  s32 lim;
  u8 *t;
  u8 *new_var3;
  s32 *new_var5;
  u16 f26;
  s32 *new_var;
  u32 k;
  t = *((void **) (((u8 *) arg0) + 0x3C));
  p38 = *((void **) (((u8 *) arg0) + 0x38));
  p3C = t;
  r6 = ((u8 *) p3C) + 0x48;
  f26 = *((u16 *) (r6 + 0x26));
  new_var4 = (u32 *) (r6 + 0x34);
  if (((s32) (*((s16 *) (r6 + 0x26)))) > 0)
  {
    result = f26 - 1;
  }
  else
  {
    if ((*((u32 *) (r6 + 0x34))) == 0)
    {
      return 0;
    }
    r4 = sub_08016238();
    if (r4 == 0)
    {
      return 0;
    }
    new_var3 = ((u8 *) p3C) + 8;
    if (sub_08014990((s32) p38) < 0)
    {
      base = D_02025FF0;
      p38 = base + 0x174C;
      cur = *((s32 *) new_var3);
      if ((*((s32 *) p38)) > (cur + ((s32) 0xFFDC0000)))
      {
        return 0;
      }
      off = (s32) 0xFFD80000;
    }
    else
    {
      base = D_02025FF0;
      new_var5 = (s32 *) (base + 0x174C);
      cur = *((s32 *) new_var3);
      if ((*((s32 *) new_var5)) < (cur + 0x240000))
      {
        return 0;
      }
      off = 0x280000;
    }
    addr = cur + off;
    val = (((s32) (*((s16 *) (((u8 *) r4) + 0x32)))) << 16) + ((s32) 0xFFFF8000);
    t = D_02021E90;
    k = *((u8 *) (base + 0x18A8));
    k = k + 1;
    k = k << 6;
    t = t + 0x127C;
    val += *((s32 *) (t + k));
    new_var = (s32 *) (((u8 *) p3C) + 0xC);
    lim = (*new_var) + ((s32) 0xFFC00000);
    if (val < lim)
    {
      val = lim;
    }
    else
      if (val > ((*new_var) + ((s32) 0xFFF00000)))
    {
      val = (*new_var) + ((s32) 0xFFF00000);
    }
    sub_0808E9AC(addr, val, 8);
    result = 6;
  }
  *((u16 *) (r6 + 0x26)) = result;
  return 1;
}

