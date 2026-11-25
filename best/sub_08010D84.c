struct A1
{
  u8 f0;
  u8 f1;
  u16 f2;
  u32 f4;
};
struct A0
{
  u8 pad[0x28];
  u16 f28;
};
void sub_08010D84(struct A0 *a0, struct A1 *a1, u16 *arg2, u32 arg3)
{
  s32 i;
  u16 *q = arg2;
  u16 mask;
  u8 b;
  b = (u8) arg3;
  i = 0;
  if ((arg2[0] & 0x8000) == 0)
  {
    i = 0x8000;
    mask = i;
    do
    {
      q += 2;
      i++;
    }
    while ((q[0] & mask) == 0);
  }
  if (i > 0)
  {
    i--;
    q = arg2 + (i * 2);
    a1->f2 = q[0];
    a1->f4 = (u32) a1->f2;
    a1->f4 = a1->f4 << 16;
    a1->f1 = (i > 0) ? (i - 1) : (i + 1);
    a1->f0 = b;
    a0->f28 = q[1];
  }
  else
  {
    a1->f2 = 0;
    a1->f4 = 0;
    a1->f1 = 0;
    a1->f0 = b | 2;
    a0->f28 = 0;
  }
}

