struct S_02025FF0
{
  u8 _0x000[0x18C2];
  u16 w;
};
extern struct S_02025FF0 D_02025FF0;
extern u32 D_08671BB0[];
extern u16 D_03000830[];
void sub_08081F10(void *arg0)
{
  u8 *self = (u8 *) arg0;
  void *tmp;
  u8 zero;
  if (sub_0800168C(arg0, 0, 0x68, 3) == 0)
  {
    _call_via_r1(arg0, *((void **) (((u8 *) arg0) + 0x24)));
    return;
  }
  tmp = sub_0800355C();
  if (tmp == 0)
  {
    sub_0806D2D0(arg0);
    return;
  }
  *((void **) (((u8 *) arg0) + 0x38)) = tmp;
  *((u32 *) (((u8 *) tmp) + 0x1C)) = 0x80000004;
  {
    u16 *pdest = (u16 *)((u8 *)tmp + 2);
    u16 spriteFlags = (u16)(0x400 | *pdest);
    *pdest = spriteFlags;
    zero = 0;
  }
  {
    u16 w = D_02025FF0.w;
    *((u16 *) tmp) = w;
    D_03000830[3] = 0x1000;
    {
      s32 idx = *((s16 *) (((u8 *) arg0) + 0x22));
      if (tmp || (&D_02025FF0))
      {
        *((u8 *) ((((u8 *) arg0) + (idx * 2)) + 0x19)) = (u8) zero;
      }
      else
      {
        *((u8 *) ((((u8 *) arg0) + (idx * 2)) + 0x19)) = (u8) zero;
      }
    }
  }
  {
    const u32 *lit = (const u32 *) 0x08671BB0;
    void *r4 = ((u8 *) arg0) + 0x18;
    _call_via_r2(r4, ((u8 *) arg0) + 0x22, *lit);
    *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) += 1;
    r4 = ((u8 *) r4) + ((*((s16 *) (self + 0x22))) * 2);
    _call_via_r1(arg0, *((u32 *) ((*((u32 *) (((u8 *) arg0) + 0x14))) + ((*((u8 *) r4)) * 4))));
  }
}
