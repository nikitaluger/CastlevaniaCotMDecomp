void sub_080C31E4(void *, void *, s32);
void sub_080C31E0(void *, s32);
void sub_080ADA18(void *arg0)
{
  u8 *r4 = (u8 *) arg0;
  int new_var;
  u8 *r2 = *((u8 **) (r4 + 0x3C));
  s32 *r3 = (s32 *) (r2 + 0x48);
  do
  {
    if ((*((u8 *) (r4 + 0x7C))) != 0)
    {
      u32 i = 0;
      s32 *lit = (s32 *) 0x08671BB0;
      u8 *r7 = r4 + 0x18;
      u8 *r6 = r4 + 0x22;
      u8 one = 1;
      do
      {
        u8 *p = (u8 *) (*(r3++));
        *((u8 *) (p + 0x90)) = one;
        i++;
      }
      while (i <= 6);
      *((s32 *) (r2 + 8)) = *((s32 *) (r4 + 0x4C));
      *((s32 *) (r2 + 0xC)) = *((s32 *) (r4 + 0x5C));
      *((u8 *) ((r4 + ((*((s16 *) (r4 + 0x22))) * 2)) + 0x19)) = 0;
      new_var = 2;
      sub_080C31E4(r7, r6, *lit);
      *((u8 *) ((r4 + ((*((s16 *) (r4 + 0x22))) * 2)) + 0x19)) += 1;
      {
        s16 idx = *((s16 *) (r4 + 0x22));
        u8 b = *((u8 *) (r7 + (idx * new_var)));
        s32 fn = *((s32 *) ((*((u8 **) (r4 + 0x14))) + (b * 4)));
        sub_080C31E0(r4, fn);
      }
    }
  }
  while (0);
}

