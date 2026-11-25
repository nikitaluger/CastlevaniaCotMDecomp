extern u8 D_02025358[];
extern u32 D_0866F824[];
extern u8 D_02025FF0[];
void sub_0808B470(u32 *arg0)
{
  u8 *p = D_02025358;
  u32 *tbl = D_0866F824;
  u32 idx = (p[0x0C] & 0xF) - 1;
  u16 *entry = (u16 *) (tbl[idx] + (arg0[0] << 2));
  if (arg0[2] == 0)
  {
    arg0[1] = entry[1];
    arg0[2] = 1;
  }
  {
    u8 *out = D_02025FF0;
    *((u16 *) (out + 0x34)) = entry[0];
    if ((--arg0[1]) == 0)
    {
      arg0[0]++;
      arg0[1] = entry[3];
      {
        *((u32 *) (out + 0x0C)) = 1;
      }
    }
  }
}

