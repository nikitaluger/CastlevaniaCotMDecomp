void sub_080C0C30(u32 dummy1, u8 *arg1, u32 dummy2)
{
  u32 mask = 1;
  u32 t = arg1[0] & mask;
  u32 mult;
  u32 tmp;
  u32 tmp2;
  s32 clamp;
  u32 r0;
  u32 r3;
  u32 r0b;
  u32 r0x;
  s32 r1x_1;
  s32 r1x_2;
  s32 r1x_3;
  s32 r1x_4;
  s32 r1x_5;
  s32 r1x_6;
  u32 r0y;
  u32 r0z;
  u32 r0final;
  u32 b13;
  u32 b12;
  u32 b0;
  if (t == 0)
  {
    goto part2;
  }
  b13 = arg1[0x13];
  b12 = arg1[0x12];
  mult = ((u32) (b13 * b12)) >> 5;
  if (arg1[0x18] == 1)
  {
    tmp = (u32) (((s32) ((s8) arg1[0x16])) + 0x80);
    tmp = tmp * mult;
    mult = tmp >> 7;
  }
  tmp2 = (u32) (((s8) arg1[0x14]) * 2);
  clamp = ((s32) tmp2) + ((s32) ((s8) arg1[0x15]));
  if (arg1[0x18] == 2)
  {
    clamp += (s32) ((s8) arg1[0x16]);
  }
  if (clamp < (-0x80))
  {
    clamp = -0x80;
  }
  else
    if (clamp > 0x7F)
  {
    clamp = 0x7F;
  }
  r0 = ((u32) (clamp + 0x80)) * mult;
  r0 = r0 >> 8;
  r0 = (r0 << 24) >> 24;
  if (r0 > 0xFF)
  {
    r0 = 0xFF;
  }
  arg1[0x10] = (u8) r0;
  r0 = ((u32) (0x7F - clamp)) * mult;
  r0 = r0 >> 8;
  r0 = (r0 << 24) >> 24;
  if (r0 > 0xFF)
  {
    r0 = 0xFF;
  }
  arg1[0x11] = (u8) r0;
  part2:
  if (arg1[0] & 4)
  {
    r0x = (u32) (((s32) ((s8) arg1[0x0E])) * ((s32) arg1[0x0F]));
    r1x_1 = (s32) ((s8) arg1[0x0C]);
    r1x_2 = r1x_1 + ((s32) r0x);
    r1x_3 = r1x_2 << 2;
    r0y = (u32) (((s32) ((s8) arg1[0x0A])) << 8);
    r1x_4 = r1x_3 + ((s32) r0y);
    r0z = (u32) (((s32) ((s8) arg1[0x0B])) << 8);
    r1x_5 = r1x_4 + ((s32) r0z);
    r1x_6 = r1x_5 + ((s32) arg1[0x0D]);
    if (arg1[0x18] == 0)
    {
      r1x_6 += (s32) (((s32) ((s8) arg1[0x16])) << 4);
    }
    arg1[0x08] = (u8) (((s32) r1x_6) >> 8);
    arg1[0x09] = (u8) r1x_6;
  }
  arg1[0] = arg1[0] & 0xFA;
}
