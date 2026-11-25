s32 sub_080C31E0(s32, s32);
extern s32 D_08671BFC;
inline int inline_fn(s32 arg0)
{
  return arg0 / 4;
}

void sub_08051D3C(void *arg0, s32 *arg1, s32 arg2, s32 arg3)
{
  void *sp0;
  s32 sp4;
  s32 sp8;
  s32 *new_var2;
  s32 new_var;
  s32 spC;
  s32 *sp10;
  s8 *sp14;
  s32 *sp18;
  s32 *var_r10;
  int new_var4;
  s32 *var_r2;
  s32 *var_r3;
  s32 temp_r0;
  s32 *new_var3;
  s32 temp_r0_2;
  s32 sp1C;
  s32 temp_r4;
  s32 var_r0;
  s32 var_r6;
  s32 var_r7;
  s32 var_r7_2;
  s32 var_r9;
  sp0 = arg0;
  new_var2 = arg1;
  sp4 = arg3;
  spC = 0 - (((s8 *) arg0)[0x6C] << 0x11);
  var_r6 = arg2 << 8;
  arg1[2] = arg1[0] + spC;
  temp_r0 = new_var2[1] + 0xFFEE0000;
  arg1[inline_fn(0x2C)] = temp_r0;
  sp8 = temp_r0;
  sp14 = ((s8 *) arg0) + 0x6C;
  sp18 = arg1 + 2;
  new_var3 = &sp8;
  sp10 = arg1 + inline_fn(0x2C);
  var_r10 = arg1 + inline_fn(0x30);
  sp1C = 4;
  var_r9 = 0;
  new_var4 = inline_fn(0x2C) + inline_fn(sp1C);
  var_r7 = 7;
  do
  {
    arg1[2 + inline_fn(sp1C)] = ((((s8 *) sp0)[0x6C] * ((var_r9 >> 8) * (sub_080C31E0(var_r6, D_08671BFC) >> 8))) + arg1[0]) + spC;
    temp_r4 = var_r6 + 0x4000;
    if (((s32) (sub_080C31E0(temp_r4, D_08671BFC) * 6)) < 0)
    {
      var_r0 = (*new_var3) + (sub_080C31E0(temp_r4, D_08671BFC) * 6);
    }
    else
    {
      var_r0 = sp8 - (sub_080C31E0(temp_r4, D_08671BFC) * 6);
    }
    arg1[new_var4] = var_r0;
    sp8 = *var_r10;
    var_r6 += 0xE00;
    if (sp4 != 0)
    {
      var_r9 += 0x30000;
    }
    else
    {
      var_r9 += 0x24000;
    }
    var_r10 += 1;
    sp1C += 4;
    var_r7 -= 1;
  }
  while (var_r7 >= 0);
  if (sp4 != 0)
  {
    var_r2 = sp18 + 1;
    var_r3 = sp10 + 1;
    var_r7_2 = 7;
    do
    {
      new_var = *var_r3;
      temp_r0_2 = new_var;
      var_r3 += 1;
      *var_r2 -= (((s32) ((char) ((temp_r0_2 + 0x120000) - arg1[1]))) >> 2) * (*sp14);
      var_r2 += 1;
      var_r7_2 -= 1;
    }
    while (var_r7_2 >= 0);
  }
}

