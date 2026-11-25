extern u8 D_02021E90[];
extern u16 D_03000830[];
extern vu8 D_04000005;
s32 sub_080C2F20(s32, s32);

void sub_080BEE6C(void)
{
  u8 *base = D_02021E90;
  u32 offB0 = 0x13B0;
  u8 *pAF = D_02021E90 + 0x13AF;
  u16 *io = D_03000830;
  u16 *p;
  u16 *p3;
  u32 i;
  u32 step;
  u32 acc;
  s32 k;

  if (base[0x13AE] <= 1)
    return;
  base[0x1361] = 6;
  *(u16 *) (base + 0x13AA) = io[0x0F];
  *(u16 *) (base + 0x13AC) = io[0x10];
  *(u16 *) (base + 0x13A6) = io[0x02];
  *(u16 *) (base + 0x13A8) = io[0x04];
  p = (u16 *) (base + 0x1364);
  for (i = 0; i <= 0x10; i++)
  {
    *p = 0xFF;
    p++;
  }
  acc = 0x00B40000;
  step = sub_080C2F20(0x000F0000, base[0x13AE] - 1);
  base[0x13B0] = 0xFF;
  k = (0x10 - base[0x13AE]) >> 1;
  if (k < ((base[0x13AE] + 0x10) >> 1))
  {
    p3 = (u16 *) (base + 0x1364) + k;
    for (;;)
    {
      *p3 = (u16) ((acc >> 16) - k - 0x4C);
      if ((u32) ((acc >> 16) - 0xB4) >= *pAF)
      {
        u8 *pp = base + offB0;
        if (*pp == 0xFF)
          *pp = (u8) k;
      }
      acc += step;
      p3++;
      k++;
      if (!(k < ((base[0x13AE] + 0x10) >> 1)))
        break;
    }
  }
  D_04000005 = 0x4B;
}
