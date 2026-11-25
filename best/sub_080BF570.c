extern u16 D_020231F4[];
extern short D_0202323A;
extern u8 D_02021E90[];
void sub_080BF570(void)
{
  u32 i = 0;
  u8 *base = D_02021E90;
  vu8 *dispstat = (vu8 *) 0x04000004;
  vu16 *bg0hofs = (vu16 *) 0x04000010;
  vu16 *bg0vofs = (vu16 *) 0x04000012;
  vu8 *new_var2;
  vu16 *bldcnt = (vu16 *) 0x04000050;
  vu8 *new_var;
  vu16 *bldy = (vu16 *) 0x04000054;
  u32 two = 2;
  u8 *new_var3;
  new_var3 = (u8 *) D_020231F4;
  do
  {
    s32 idx2 = i * 2;
    u16 val = *((u16 *) (new_var3 + idx2));
    s32 next = i + 1;
    if (val == 0xFF)
    {
      if (((*dispstat) & two) == 0)
      {
        while (((*((vu8 *) 0x04000004)) & two) == 0)
        {
          ;
        }

      }
      *bg0hofs = D_0202323A;
      *bg0vofs = *((u16 *) (base + 0x13AC));
      *bldcnt = *((u16 *) (base + 0x13A6));
      *bldy = *((u16 *) (base + 0x13A8));
    }
    else
    {
      int v;
      if (i < base[0x13B0])
      {
        v = *((u16 *) (base + 0x13B2));
      }
      else
      {
        v = *((u16 *) (base + 0x13B4));
      }
      new_var = (vu8 *) 0x04000004;
      if (((*new_var) & two) == 0)
      {
        while (((*new_var) & two) == 0)
        {
          ;
        }

      }
      *bg0hofs = v;
      *bg0vofs = *((u16 *) (((u8 *) D_020231F4) + idx2));
      *bldcnt = 0x20FE;
      D_0202323A += 0;
      *bldy = 6;
    }
    if ((*new_var) & two)
    {
      new_var2 = new_var;
      while ((*new_var2) & two)
      {
        ;
      }

    }
    i = next;
  }
  while (i <= 0x10);
}
