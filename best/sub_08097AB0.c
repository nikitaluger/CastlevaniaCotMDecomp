extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_08097CD4(void);
extern u8 D_02025FF0[];
extern u16 D_020213DC;
extern u8 D_08101368[];
extern void *D_08671BB0;

void sub_08097AB0(u8 *arg0)
{
  s16 idx;
  u8 *base;
  u8 *p;
  u8 *r4;
  s32 zero;
  u16 t;
  u32 off;
  s32 one;
  u16 *pd;
  u16 *pd2;

  r4 = *((u8 **) (arg0 + 0xAC));
  sub_0800168C(arg0, 0, 0x10C, 0);
  p = *((u8 **) (arg0 + 0x3C));
  if (p == 0)
  {
    sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
    return;
  }
  *((void **) (p + 4)) = *((void **) (arg0 + 0x24));
  *((void **) (arg0 + 0x24)) = (void *) sub_08097CD4;
  t = *((u16 *) (*((u8 **) (r4 + 4)) + 6));
  *((u8 **) p) = (u8 *) (D_08101368 + (t * 4));
  pd = (u16 *) (p + 0x108);
  zero = 0;
  *pd = zero;
  D_020213DC = zero;
  off = 0xC6 << 5;
  pd2 = (u16 *) (D_02025FF0 + off);
  one = 1;
  *pd2 = one;
  *((u16 *) (arg0 + 0x02)) |= 0x1000;
  idx = *((s16 *) (arg0 + 0x22));
  arg0[(idx * 2) + 0x19] = zero;
  {
    void **lit = &D_08671BB0;
    base = arg0 + 0x18;
    sub_080C31E4(base, arg0 + 0x22, *lit);
  }
  idx = *((s16 *) (arg0 + 0x22));
  arg0[(idx * 2) + 0x19]++;
  idx = *((s16 *) (arg0 + 0x22));
  base = base + (idx * 2);
  sub_080C31E0(arg0, *((void **) ((*((u32 *) (arg0 + 0x14))) + (base[0] * 4))));
}
