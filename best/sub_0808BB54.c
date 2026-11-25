extern u8 D_02025FF0[];
extern u32 D_0866F840[];
extern u16 D_03000830[];
void sub_0808BB54(void)
{
  u8 *base = D_02025FF0;
  u8 new_var;
  u8 *p = base + 0x50;
  u32 r;
  if ((*p) != 0x0F)
  {
    r = D_0866F840[new_var = *p] + ((new_var = base[0x51]) * 0x60);
  }
  else
  {
    r = D_0866F840[new_var];
  }
  D_03000830[2] = *((u16 *) (r + 0x5A));
  D_03000830[3] = 0x0808;
  D_03000830[4] = 0;
}

