struct S_03000830
{
  u8 _[4];
  u16 f04;
  u16 f06;
};
s32 sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
void sub_0800D070(void *arg0)
{
  struct S_03000830 *io = (struct S_03000830 *) 0x03000830;
  u16 v1;
  u8 *b;
  u8 *p;
  s32 zero = 0;
  s32 idx = 0;
  s8 sb;
  u8 b2;
  v1 = (io->f04 = 0x3F53);
  b = (u8 *) 0x020278D0;
  p = b;
  p += 0x67;
  sb = ((s8 *) p)[idx];
  io->f06 = sb | ((0x10 - sb) << 8);
  b2 = *((volatile u8 *) p);
  sb = ((s8 *) p)[idx];
  if (sb == 0)
  {
    io->f04 = sb;
    *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = zero;
    {
      s32 *nv = (s32 *) 0x08671BB0;
      sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *nv);
    }
    {
      u8 *p2 = (u8 *) ((((u32) (*((s16 *) (((u8 *) arg0) + 0x22)))) * 2) + ((u32) arg0));
      p2[0x19] = (u8) (p2[0x19] + 1);
    }
    {
      s32 idx2 = (*((s16 *) (((u8 *) arg0) + 0x22))) * 2;
      u8 *base18 = ((u8 *) arg0) + 0x18;
      u8 b = *(base18 + idx2);
      u8 **tbl = *((u8 **) (((u8 *) arg0) + 0x14));
      sub_080C31E0(arg0, (s32) tbl[b]);
    }
  }
  else
  {
    s32 v = b2 - 2;
    *p = v;
    if (((s8) v) < 0)
    {
      *b = zero;
    }
  }
}
