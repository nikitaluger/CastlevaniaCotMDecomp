struct S_02021E90
{
  u8 _0[0x143C];
  u8 unk143C;
  u8 _143D[0x1444 - 0x143D];
  u8 unk1444;
  u8 _1445[0x1454 - 0x1445];
  s32 unk1454;
  u8 _1458[0x145C - 0x1458];
  u8 unk145C;
  u8 _145D[0x146C - 0x145D];
  u16 unk146C;
};
struct S_02025358
{
  u8 _0[0x0C];
  u8 unkC;
};
struct S_02025FF0
{
  u8 _0[0x28];
  u16 unk28;
};
extern struct S_02021E90 D_02021E90;
extern struct S_02025358 D_02025358;
extern struct S_02025FF0 D_02025FF0;
s32 sub_08060214(void)
{
  struct S_02021E90 *new_var;
  struct S_02025358 *p25358 = &D_02025358;
  struct S_02021E90 *p21E90 = &D_02021E90;
  u8 *p145C = &(&D_02021E90)->unk145C;
  short flags = *p145C;
  u32 one = 1;
  if (!(flags & one))
  {
    *p145C = flags | 1;
    goto ret2;
  }
  if ((!(p25358->unkC & 0x80)) && (p25358->unkC != 0))
  {
    do
    {
      if (!(D_02025FF0.unk28 & 1))
      {
        if (p25358->unkC)
        {
          goto ret2;
        }
        else
        {
          goto ret2;
        }
      }
    }
    while (0);
  }
  else
  {
    new_var = p21E90;
    if (!(new_var->unk146C & 1))
    {
      goto ret2;
    }
  }
  new_var = &D_02021E90;
  {
    u8 *flagPtr = &new_var->unk145C;
    u8 f = *flagPtr;
    if (f & 2)
    {
      *flagPtr = f & 0xFD;
      p21E90->unk143C = (&D_02021E90)->unk1444;
      f = *flagPtr;
    }
    *flagPtr = (flags = f & 0xFE);
  }
  (&D_02021E90)->unk1454++;
  return 0;
  ret2:
  return 2;

}
