extern u8 D_02025FF0[];
s32 sub_080A89A4(void *arg0)
{
  s32 *new_var;
  s32 v;
  if ((*((u8 *) (((u8 *) arg0) + 0x4C))) == 0)
  {
    u8 *base = D_02025FF0;
    volatile unsigned int off;
    v = *((s32 *) (base - (-off)));
    if (v <= 0x0087FFFF)
    {
      return 0;
    }
    if (v > 0x01780000)
    {
      return 2;
    }
    return 1;
  }
  else
  {
    u8 *base = D_02025FF0;
    u32 off = 0x174C;
    new_var = (s32 *) (base + off);
    v = *new_var;
    if (v <= 0x0087FFFF)
    {
      return 2;
    }
    if (v > 0x01780000)
    {
      return 0;
    }
    off = 0x174C;
    return 1;
  }
}

