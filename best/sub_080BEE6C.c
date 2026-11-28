extern u8 gCameraState[];
extern u16 gCrossfadeGfxState[];
extern vu8 gVcountCompare;
s32 divideInt(s32, s32);
void sub_080BEE6C(void)
{
  u8 *base;
  u32 offB0;
  u32 key;
  u8 *pAF;
  u16 *io;
  u16 *p;
  u16 *p3;
  u32 i;
  u32 i_loop;
  u32 step;
  
  u16 temp;
  u16 temp2;
  u16 temp3;
  base = gCameraState;
  if (base[0x13AE] <= 1)
  {
    return;
  }
  do
  {
    offB0 = 0x13B0;
  }
  while (0);
  io = gCrossfadeGfxState;
  do {
  u16 temp4;
  base[0x1361] = 6;
  temp = io[0x0F];
  *((u16 *) (base + 0x13AA)) = temp;
  temp2 = io[0x10];
  *((u16 *) (base + 0x13AC)) = temp2;
  temp3 = io[0x02];
  *((u16 *) (base + 0x13A6)) = temp3;
  temp4 = io[0x04];
  *((u16 *) (base + 0x13A8)) = temp4;
  p = (u16 *) (base + 0x1364); } while (0);
  for (i_loop = 0; i_loop <= 0x10; i_loop++)
  {
    do
    {
      *p = 0xFF;
    }
    while (0);
    p++;
  }

  i = 0x00B40000;
  step = divideInt(0x000F0000, base[0x13AE] - 1);
  base[0x13B0] = 0xFF;
  i_loop = (0x10 - base[0x13AE]) >> 1;
  if (i_loop < ((base[0x13AE] + 0x10) >> 1))
  {
    pAF = base + 0x13AF;
    p3 = ((u16 *) (base + 0x1364)) + i_loop;
    key = offB0;
    for (;;)
    {
      *p3 = (u16) (((i >> 16) - i_loop) - 0x4C);
      if (((u32) ((i >> 16) - 0xB4)) >= (*pAF))
      {
        u8 *pp;
        pp = base + key;
        if ((*pp) == 0xFF)
        {
          *pp = (u8) i_loop;
        }
      }
      i += step;
      p3++;
      i_loop++;
      if (!(i_loop < ((base[0x13AE] + 0x10) >> 1)))
      {
        break;
      }
    }

  }
  gVcountCompare = 0x4B;
}
