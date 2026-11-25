extern void sub_08005E80(s32);
extern void sub_08007ED0(void);
extern void sub_08007EF8(void);
extern s16 sub_0800BF70(void *);
extern s32 sub_080C31E8(s32, s32, s32, s32);
extern u8 D_02025368[];
extern u8 D_020253F4[];
extern u8 D_02025FF0[];
extern u8 D_020278D0[];
extern u8 D_08671BD8[];
void sub_0800A9EC(u8 *arg0)
{
  u8 *r5 = arg0;
  u8 *new_var;
  u8 *r8 = D_02025368;
  u8 *r4 = *((u8 **) (arg0 + 0x3C));
  u8 r6;
  u8 *r7;
  u8 *r9;
  u8 *r10;
  u8 *r6p;
  u8 *r3;
  u8 r2;
  u8 *pp;
  u8 zero;
  s16 ret;
  *((u8 *) ((*((u32 *) (r4 + (0xC6 << 3)))) + 0x40)) = 0;
  r6 = *((u8 *) (r4 + 0x639));
  if (r6 != 0)
  {
    sub_08005E80(0x15C);
    sub_08007ED0();
    r2 = 0;
    r7 = r5 + 0x50;
    r9 = r5 + 0x18;
    new_var = r8 + 1;
    r10 = r5 + 0x22;
    r6p = new_var;
    r3 = r4 + 0x600;
    do
    {
      *(r6p + r2) = *(r3 + r2);
      r2++;
    }
    while (r2 <= 7);
    ret = sub_0800BF70(r4);
    zero = 0;
    *((s16 *) D_020253F4) = ret;
    sub_08007EF8();
    D_02025FF0[8] = *r7;
    *((s32 *) D_020278D0) = 5;
    pp = (u8 *) ((((s32) (*((s16 *) (r5 + 0x22)))) * 2) + ((u32) r5));
    *((u8 *) (pp + 0x17)) = zero;
    sub_080C31E8((s32) r9, (s32) r10, 0x11, *((s32 *) D_08671BD8));
  }
  else
  {
    sub_08005E80(0x159);
    *((u8 *) (r4 + 0x635)) = 1;
    pp = (u8 *) ((((s32) (*((s16 *) (r5 + 0x22)))) * 2) + ((u32) r5));
    *((u8 *) (pp + 0x17)) = r6;
    {
      s32 *pd = (s32 *) D_08671BD8;
      sub_080C31E8((s32) (r5 + 0x18), (s32) (r5 + 0x22), 0x10, *pd);
    }
  }
}

