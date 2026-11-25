s32 sub_0800583C(s32);
s32 sub_08012A94(s32, s32, s32);
void sub_0805077C(s32, s32, s16);
void sub_080C31E4(void *, void *, s32);
s32 sub_080C36E4(s16, s32);
void sub_0804FD4C(void *arg0)
{
  s16 temp_r0;
  s16 temp_r0_2;
  s16 temp_r1;
  s16 temp_r1_2;
  s32 temp_r0_3;
  s32 temp_r4;
  s32 temp_r4_2;
  s32 temp_r4_3;
  s32 var_r0;
  s32 var_r2;
  u16 *temp_r2;
  u8 *p52;
  s32 *pBB0;
  void *temp_r5;
  void *temp_r6;
  s32 idx;
  u16 mask = 1;
  temp_r6 = *((void **) (((u8 *) arg0) + 0x3C));
  temp_r5 = temp_r6 + 0x48;
  if ((sub_080C36E4(*((s16 *) temp_r5), 0xC) << 0x10) == 0)
  {
    idx = *((s16 *) (((u8 *) temp_r5) + 4)) * 2;
    p52 = (u8 *)temp_r6 + 0x52;
    temp_r2 = (u16 *)(p52 + idx);
    if (*temp_r2 & mask)
    {
      temp_r0 = (s16) (*temp_r2);
      temp_r4 = ((s32) (temp_r0 + (((u32) temp_r0) >> 0x1F))) >> 1;
      temp_r1 = *((s16 *) (((u8 *) temp_r5) + 8));
      if (temp_r4 == (temp_r1 + 1))
      {
        var_r2 = 0x60000;
      }
      else
        if (temp_r4 == temp_r1)
      {
        var_r2 = 0xFFFA0000;
      }
      else
      {
        var_r2 = sub_0800583C(0x10000) * 4;
      }
      var_r0 = (*((s32 *) (((u8 *) temp_r6) + 8))) + ((temp_r4 + 1) * 0x160000);
    }
    else
    {
      temp_r0_2 = (s16) (*temp_r2);
      temp_r4_2 = ((s32) (temp_r0_2 + (((u32) temp_r0_2) >> 0x1F))) >> 1;
      temp_r1_2 = *((s16 *) (((u8 *) temp_r5) + 6));
      if (temp_r4_2 == (temp_r1_2 + 1))
      {
        var_r2 = 0xFFFA0000;
      }
      else
        if (temp_r4_2 == temp_r1_2)
      {
        var_r2 = 0x60000;
      }
      else
      {
        var_r2 = sub_0800583C(0x10000) * 4;
      }
      var_r0 = (*((s32 *) (((u8 *) temp_r6) + 8))) - ((temp_r4_2 + 1) * 0x160000);
    }
    temp_r4_3 = var_r0 + var_r2;
    temp_r0_3 = sub_08012A94(temp_r4_3, *((s32 *) (((u8 *) temp_r6) + 0xC)), 9);
    if (temp_r0_3 <= 0x3FFFFF)
    {
      sub_0805077C(temp_r4_3, (*((s32 *) (((u8 *) temp_r6) + 0xC))) + temp_r0_3, *((s16 *) (((u8 *) temp_r6) + 0x1C)));
    }
    *((s16 *) (((u8 *) temp_r5) + 4)) = (*((s16 *) (((u8 *) temp_r5) + 4))) + 1;
  }
  *((s16 *) temp_r5) = (*((s16 *) temp_r5)) + 1;
  if ((*((s16 *) (((u8 *) temp_r5) + 4))) > 9)
  {
    *((s16 *) temp_r5) = 0xB4;
    *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
    pBB0 = (s32 *)0x08671BB0;
    sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *pBB0);
  }
}
