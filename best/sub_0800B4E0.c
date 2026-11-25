extern u8 D_080CAB1C[];
extern void sub_08005E80(s32);
extern void sub_0800BDBC(s32, u8 *, s32);
extern s32 sub_080C2F24(s32, s32);
extern void _call_via_r2(void *, void *, void *);
struct P7_0800B4E0
{
  u8 _0[0x639];
  u8 f639;
};
struct Self_0800B4E0
{
  u8 _0[0x22];
  s16 f22;
  u8 _24[0x18];
  struct P7_0800B4E0 *f3C;
  u8 _40[0x18];
  s8 f58;
  u8 _59[3];
  s8 f5c;
};
struct Base_0800B4E0
{
  u8 _0[0x12A2];
  u16 f12A2;
  u8 _12A4[0x1C8];
  u16 f146C;
  u8 _146E[2];
  u16 f1470;
};
void sub_0800B4E0(struct Self_0800B4E0 *arg0)
{
  u8 *new_var;
  s32 r9;
  struct Base_0800B4E0 *base;
  u8 *new_var3;
  u16 w;
  struct P7_0800B4E0 *r7;
  s8 *p5c;
  s8 *p58;
  s8 var_r0;
  int new_var2;
  s8 var_r0_2;
  s8 t2;
  s8 t2_2;
  u8 *new_var4;
  s8 t0;
  volatile unsigned long t0_2;
  u8 t1;
  u8 t1_2;
  u8 t3;
  u8 *pa;
  u8 *pb;
  r7 = arg0->f3C;
  p5c = &arg0->f5c;
  r9 = p5c[0];
  base = (struct Base_0800B4E0 *) 0x02021E90;
  w = base->f1470;
  if ((0xC0 & w) != 0xC0)
  {
    if (0x40 & w)
    {
      t1 = (u8) p5c[0];
      if (p5c[0] <= 8)
      {
        var_r0 = t1 + 0x1B;
      }
      else
      {
        var_r0 = t1 - 9;
      }
      goto block_9;
    }
    if (0x80 & w)
    {
      t1_2 = (u8) p5c[0];
      if (p5c[0] > 0x1A)
      {
        var_r0 = t1_2 - 0x1B;
      }
      else
      {
        var_r0 = t1_2 + 9;
      }
      block_9:
      p5c[0] = var_r0;

    }
  }
  w = base->f1470;
  if ((0x30 & w) != 0x30)
  {
    if (0x20 & w)
    {
      if (sub_080C2F24(p5c[0], 9) == 0)
      {
        var_r0_2 = ((u8) p5c[0]) + 8;
      }
      else
      {
        var_r0_2 = ((u8) p5c[0]) - 1;
      }
      goto block_19;
    }
    if (0x10 & w)
    {
      if (sub_080C2F24(p5c[0], 9) == 8)
      {
        var_r0_2 = ((u8) p5c[0]) - 8;
      }
      else
      {
        var_r0_2 = ((u8) p5c[0]) + 1;
      }
      block_19:
      p5c[0] = var_r0_2;

    }
  }
  p58 = &arg0->f58;
  w = base->f1470;
  if ((0x300 & w) != 0x300)
  {
    if (0x200 & w)
    {
      p58[0] = ((u8) p58[0]) - 1;
    }
    w = base->f1470;
    if (0x100 & w)
    {
      p58[0] = ((u8) p58[0]) + 1;
    }
    if (p58[0] < 0)
    {
      p58[0] = 0;
    }
    if (p58[0] > 7)
    {
      p58[0] = 7;
    }
    if (0x300 & w)
    {
      sub_08005E80(0x156);
    }
  }
  if (8 & base->f146C)
  {
    if (((u8) p5c[0]) == 0x23)
    {
      r7->f639 = 1;
      *((u8 *) ((((u8 *) arg0) + (arg0->f22 * 2)) + 0x19)) = 0;
      goto block_57;
    }
    p5c[0] = 0x23;
    goto block_35;
  }
  block_35:
  if (r9 != p5c[0])
  {
    sub_08005E80(0x156);
  }

  if (2 & base->f146C)
  {
    t2 = p58[0];
    if (t2 == 0)
    {
      r7->f639 = (u8) t2;
      *((u8 *) ((((u8 *) arg0) + (arg0->f22 * 2)) + 0x19)) = (u8) t2;
      goto block_57;
    }
    sub_08005E80(0x158);
    t0 = p58[0];
    new_var2 = 0x600;
    pa = (((u8 *) r7) + new_var2) + t0;
    if ((t0 == 7) && ((*pa) != 0))
    {
      *pa = 0;
    }
    else
    {
      p58[0] = ((u8) p58[0]) - 1;
      *((((u8 *) r7) + new_var2) + p58[0]) = 0;
    }
    goto block_44;
  }
  block_44:
  if (!(1 & base->f146C))
  {
    goto block_60;
  }

  t3 = D_080CAB1C[p5c[0]];
  if (t3 != 0xFE)
  {
    if (t3 != 0xFF)
    {
      *((((u8 *) r7) + new_var2) + p58[0]) = t3;
      if (p58[0] <= 6)
      {
        p58[0] = ((u8) p58[0]) + 1;
      }
      else
      {
        p5c[0] = 0x23;
      }
      sub_08005E80(0x157);
      goto block_60;
    }
    r7->f639 = 1;
    sub_0800BDBC((s32) (((u8 *) r7) + new_var2), (u8 *) r7, ((0xC & base->f12A2) << 0xC) + 0x06004A20);
    *((u8 *) ((((u8 *) arg0) + (arg0->f22 * 2)) + 0x19)) = 0;
    goto block_57;
  }
  t2_2 = p58[0];
  r7->f639 = (u8) t2_2;
  if (t2_2 == 0)
  {
    *((u8 *) ((((u8 *) arg0) + (arg0->f22 * 2)) + 0x19)) = (u8) t2_2;
    new_var = (u8 *) arg0;
    new_var4 = new_var + 0x22;
    block_57:
    _call_via_r2(new_var + 0x18, new_var4, *((void **) 0x08671BB0));

    return;
  }
  sub_08005E80(0x158);
  t0_2 = p58[0];
  pb = (((u8 *) r7) + new_var2) + t0_2;
  if ((t0_2 == 7) && ((*pb) != 0))
  {
    *pb = 0;
  }
  else
  {
    new_var3 = (u8 *) r7;
    p58[0] = ((u8) p58[0]) - 1;
    *((new_var3 + new_var2) + p58[0]) = 0;
  }
  block_60:
  sub_0800BDBC((s32) (((u8 *) r7) + new_var2), (u8 *) r7, ((0xC & base->f12A2) << 0xC) + 0x06004A20);

}

