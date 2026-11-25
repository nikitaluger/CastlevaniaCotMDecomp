extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, u32);
extern u8 D_02021E90[];
extern u8 D_020278D0[];
extern u8 D_080CAFA8[];
extern u32 D_08671BB0;
inline u16 inline_fn(u8 *arg0)
{
  return *((u16 *) (arg0 + 0x12A0));
}

void sub_0800CDBC(u8 *arg0)
{
  u8 *pt;
  u32 mask;
  u8 new_var2;
  u8 *pl;
  u8 *pD;
  u8 *p64;
  u8 *p1;
  u8 *p2;
  u8 *p3;
  u32 *new_var;
  u32 v;
  u32 *p;
  u8 *base18;
  s32 i2;
  pt = D_02021E90;
  mask = 0xDFFF;
  *((u16 *) (pt + 0x1260)) = (*((u16 *) (pt + 0x1260))) & mask;
  pl = D_080CAFA8;
  pD = D_020278D0;
  p64 = pD + 0x64;
  new_var2 = (*(pl + ((*((u8 *) p64)) * 4))) << 2;
  p1 = pl + 1;
  p2 = pl + 2;
  p3 = pl + 3;
  v = ((*(p1 + ((*((u8 *) p64)) * 4))) << 8) | new_var2;
  *((u16 *) (pt + 0x1262)) = v;
  if ((*(p2 + ((*((u8 *) p64)) * 4))) == 0xFF)
  {
    *((u16 *) (pt + 0x12A0)) = (*((u16 *) (pt + 0x12A0))) | 0x2000;
  }
  else
  {
    *((u16 *) (pt + 0x12A0)) = inline_fn(pt) & mask;
    v = ((*(p3 + ((*((u8 *) p64)) * 4))) << 8) | ((*(p2 + ((*((u8 *) p64)) * 4))) << 2);
    *((u16 *) (pt + 0x12A2)) = v;
  }
  *((u8 *) (pD + 0x67)) = 0;
  {
    u8 *p19 = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (p19 + 0x19)) = 0;
  }
  new_var = &D_08671BB0;
  base18 = arg0 + 0x18;
  p = new_var;
  sub_080C31E4(base18, arg0 + 0x22, *p);
  {
    u8 *p19 = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (p19 + 0x19)) = (*((u8 *) (p19 + 0x19))) + 1;
  }
  i2 = (*((s16 *) (arg0 + 0x22))) * 2;
  sub_080C31E0((s32) arg0, *((s32 *) ((*((u32 *) (arg0 + 0x14))) + (((u32) (*((u8 *) (base18 + i2)))) * 4))));
}

