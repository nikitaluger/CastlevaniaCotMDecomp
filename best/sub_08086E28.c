extern u8 D_02025368[];
extern u8 D_02025FF0[];
void sub_08086E28(void)
{
  u8 *r5;
  u8 r2;
  u32 r4;
  u8 *p0;
  u8 r3;
  u32 tmp;
  u8 *p1;
  u8 r4v;
  u32 r1v;
  u32 *new_var;
  u32 r0;
  u32 r2v;
  u8 *p2;
  r5 = D_02025368;
  r2 = D_02025FF0[0x14ED];
  r4 = 0x305;
  p0 = r5 + r4;
  r3 = *p0;
  r1v = r3 << 4;
  tmp = r1v;
  r4 = r4 - 1;
  p1 = r5 + r4;
  r4v = *p1;
  tmp = tmp + r4v;
  if (r2 != tmp)
  {
    return;
  }
  r1v = r3 - 1;
  r0 = (r1v << 2) + r1v;
  r0 = r0 << 1;
  new_var = &r0;
  r0 = (*new_var) - 1;
  r0 = r4v + (*new_var);
  r2v = 0xC8 << 2;
  p2 = r5 + r2v;
  r0 = r0 + ((u32) p2);
  *((u8 *) (*new_var)) = 1;
}

