extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_08014900(s32);
extern s32 sub_0801491C(s32);
extern s32 sub_08014938(s32);
extern void sub_080C31E8(void *, void *, s32, void *);
extern u32 D_08671BD0;
void sub_0802A540(u8 *arg0)
{
  u8 *r5 = arg0;
  u8 *r7 = *((u8 **) (arg0 + 0x38));
  u8 *r4 = *((u8 **) (arg0 + 0x3C));
  u8 *r9 = r4 + 0x34;
  u8 *new_var;
  u8 *r6 = r4 + 0x48;
  u32 one;
  u16 flag;
  u8 *p;
  u8 z8;
  s32 z32;
  flag = *((u16 *) (r4 + 0x02));
  *((s32 *) ((*((u8 **) (arg0 + 0x3C))) + 0x10)) = z32;
  one = 1;
  if (one & flag)
  {
    *((s32 *) (r4 + 0x10)) = 0;
    p = (u8 *) ((((s32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (p + 0x19)) = 0;
    {
      u32 *pd = &D_08671BD0;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 3, (void *) (*pd));
    }
    return;
  }
  if ((*((s16 *) (r6 + 0x02))) == 0)
  {
    if ((sub_08014900(*((s32 *) (r4 + 0x08))) <= 0xE0000) && (sub_0801491C(*((s32 *) (r4 + 0x0C))) <= 0x120000))
    {
      if ((*((u16 *) (r7 + 0x02))) & 0x10)
      {
        if (sub_08014938(*((s32 *) (r4 + 0x08))) > 0)
        {
          *((s16 *) (r6 + 0x02)) = one;
        }
      }
      else
        if (sub_08014938(*((s32 *) (r4 + 0x08))) < 0)
      {
        *((s16 *) (r6 + 0x02)) = one;
      }
    }
  }
  if ((*((s16 *) (r6 + 0x02))) == 1)
  {
    sub_08011368(r7, r9, 0, 0);
    z8 = 0;
    new_var = (*((u8 **) (arg0 + 0x3C))) + 0x10;
    z32 = 0;
    *((u16 *) (r6 + 0x00)) = 0xF0;
    *((s32 *) new_var) = z32;
    p = (u8 *) ((((s32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (p + 0x19)) = z8;
    {
      u32 *pd = &D_08671BD0;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 2, (void *) (*pd));
    }
    return;
  }
  sub_08011368(r7, r9, 0, 1);
}

