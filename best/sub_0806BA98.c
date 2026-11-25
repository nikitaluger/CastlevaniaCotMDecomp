extern void sub_08005E80(s32);
extern void sub_0806A7AC(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern u8 D_02025368[];
struct S_02025FF0
{
  u8 _0[0x24];
  s32 f24;
  u16 f28;
  u16 f2A;
};
struct S_02021E90
{
  u8 _0[0x146C];
  u16 f146C;
  u16 f146E;
};
extern struct S_02025FF0 D_02025FF0;
extern volatile struct S_02021E90 D_02021E90;
s32 sub_0806BA98(u8 *arg0, void *arg1, u8 *arg2, u8 *arg3)
{
  u8 *base = D_02025368;
  struct S_02025FF0 *pf = &D_02025FF0;
  u16 new_var;
  u16 v;
  int new_var2;
  s32 z1 = 0;
  u8 z2 = 0;
  if (pf->f24)
  {
    if (((*((u16 *) (base + 0x3C0))) & pf->f28) == 0)
    {
      return 0;
    }
  }
  else
    if (((*((u16 *) (base + 0x3C0))) & D_02021E90.f146C) == 0)
  {
    return 0;
  }
  if (pf->f24)
  {
    v = pf->f2A;
  }
  else
  {
    v = D_02021E90.f146E;
  }
  if (!(v & 0x20))
  {
    if (pf->f24)
    {
      ;
      if (!(pf->f2A & 0x10))
      {
        return 0;
      }
    }
    else
    {
      if (!(D_02021E90.f146E & 0x10))
      {
        return 0;
      }
      *((s32 *) (arg2 + 0x64)) = 0x11;
    }
  }
  if ((*((u8 *) (base + 0x3C9))) == 0)
  {
    return 0;
  }
  sub_08005E80(0x6A);
  *((s32 *) (arg3 + 8)) = z1;
  sub_0806A7AC(arg1, arg2, 0x1D);
  new_var2 = 0x22;
  *((u16 *) ((*((u32 *) (arg2 + 0x130))) + 0x0E)) = *((u16 *) (base + 0x2E0));
  *((u8 *) ((arg0 + ((*((s16 *) (arg0 + new_var2))) * 2)) + 0x19)) = z2;
  sub_080C31E8(arg0 + 0x18, arg0 + new_var2, 0x14, *((u32 *) 0x08671BD0));
  return 1;
}

