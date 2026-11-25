void sub_080C02B0(u32 a, u8 *p)
{
  u8 v;
  v = 0;
  p[0x16] = 0;
  p[0x1A] = v;
  v = p[0x18];
  if (v == 0)
  {
    v = 0x0C;
  }
  else
  {
    v = 0x03;
  }
  p[0] |= v;
}

