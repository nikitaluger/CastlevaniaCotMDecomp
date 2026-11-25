extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
void sub_08025F38(u8 *arg0)
{
  u8 *base;
  u8 *p0;
  u8 *p;
  u32 *q;
  s32 count;
  s32 i;
  s32 j;
  s32 v;
  u8 *p18;
  s32 *lit;
  base = *((u8 **) (arg0 + 0x3C));
  count = 0;
  i = 0;
  p0 = base;
  p0 += 0x68;
  p = base;
  p += 0x68;
  do
  {
    v = *((s32 *) p);
    if (v == 0)
    {
      if (v < i)
      {
        s32 m = 1;
        q = (u32 *) p0;
        j = i;
        do
        {
          u8 *obj = (u8 *) (*(q++));
          *((u16 *) (obj + 0x64)) |= m;
          j--;
        }
        while (j != 0);
      }
      sub_080C31E0(arg0, *((void **) (arg0 + 0x24)));
      return;
    }
    if (((*((u16 *) (((u8 *) (*((s32 *) p))) + 2))) & 0x1000) != 0)
    {
      count++;
    }
    p += 4;
    i++;
  }
  while (i <= 4);
  if (count <= 4)
  {
    if (1)
    {
      return;
    }
  }
  *((u8 *) ((arg0 + ((*((s16 *) (0x22 + arg0))) * 2)) + 0x19)) = 0;
  lit = (s32 *) 0x08671BB0;
  p18 = arg0 + 0x18;
  sub_080C31E4(p18, arg0 + 0x22, *lit);
  *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) += 1;
  p18 = p18 + ((*((s16 *) (arg0 + 0x22))) * 2);
  sub_080C31E0(arg0, *((void **) ((((u32) (*p18)) * 4) + (*((u32 *) (arg0 + 0x14))))));
}

