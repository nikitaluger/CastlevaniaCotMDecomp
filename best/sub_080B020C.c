extern s32 sub_08005910(s32, u32);
extern unsigned int sub_080C2F4C(s32);
extern s32 sub_080C31E0(s32, s32);
inline int inline_fn(s8 arg0, volatile long arg1)
{
  return arg0 * (arg1 + 0xFFFFC000);
}

inline s32 *inline_fn2(int arg0)
{
  return (s32 *) arg0;
}

void sub_080B020C(void *arg0)
{
  s32 sp0;
  s32 sp8;
  int new_var5;
  void *spC;
  s32 temp_r4;
  void *new_var;
  s32 temp_r4_2;
  s32 temp_r4_3;
  s32 temp_r4_4;
  s8 var_r9;
  void *new_var2;
  void **new_var8;
  volatile long sp4;
  u32 var_r2;
  u32 var_r2_2;
  int new_var9;
  s8 new_var3;
  u8 **new_var6;
  u8 **temp_r6;
  u8 **var_r1;
  void *temp_r0;
  u8 *new_var4;
  void *temp_r0_2;
  s32 *new_var7;
  void *temp_r7;
  temp_r7 = *((void **) (((u8 *) arg0) + 0x3C));
  temp_r6 = (u8 **) (((u8 *) temp_r7) + 0x48);
  temp_r0 = *((void **) (((u8 *) arg0) + 0x28));
  arg0 = (u8 *) arg0;
  new_var5 = 0x48;
  spC = *((void **) (((u8 *) temp_r0) + 0x3C));
  *((u8 *) ((((u8 *) temp_r7) + new_var5) + 0x60)) = *((u8 *) (arg0 + 0x54));
  *((u8 *) (temp_r6[1] + 0x60)) = *((u8 *) (arg0 + 0x54));
  *((u8 *) (temp_r6[2] + 0x60)) = *((u8 *) (arg0 + 0x54));
  new_var = arg0;
  var_r9 = -1;
  new_var8 = (void **) (((u8 *) temp_r0) + 0x38);
  if (0x10 & (*((u16 *) (((u8 *) (*new_var8)) + 2))))
  {
    var_r9 = 1;
  }
  var_r2 = 0;
  var_r1 = temp_r6;
  new_var4 = (u8 *) temp_r7;
  do
  {
    new_var3 = var_r9;
    (*var_r1)[0x58] = (u8) new_var3;
    temp_r0_2 = *var_r1;
    var_r1 = var_r1 + 1;
    ((u8 *) temp_r0_2)[0x54] = (u8) (1 & (*((u8 *) spC)));
    var_r2 = var_r2 + 1;
  }
  while (var_r2 <= 3U);
  temp_r4 = (sp8 = *((s32 *) (arg0 + 0x5C)));
  sp0 = temp_r4;
  new_var2 = (arg0 = (u8 *) spC);
  {
    s32 t2 = (*((s32 *) (new_var2 + 8))) + (new_var9 = 1 * (*inline_fn2(0x08670240 + ((*((s32 *) (((u8 *) new_var) + 0x4C))) * 8))));
    *((s32 *) (((u8 *) temp_r7) + 8)) = t2;
    *((s32 *) (new_var4 + 0x0C)) = (*((s32 *) (arg0 + 0x0C))) + (*inline_fn2(0x08670244 + (((s8) ((u8) (*((s8 *) (arg0 + 0x4C))))) * 8)));
    *((s32 *) (0x6C + temp_r6[0])) = t2;
    *((s32 *) (temp_r6[0] + 0x7C)) = *((s32 *) (((u8 *) temp_r7) + 0x0C));
  }
  new_var7 = inline_fn2(0x08671BFC);
  temp_r4_2 = var_r9 * sp0;
  *((s32 *) (temp_r6[1] + 0x6C)) = (*((s32 *) (temp_r6[0] + 0x6C))) + ((sub_080C31E0(temp_r4_2 + 0x10000, *inline_fn2(0x08671BFC)) >> 8) << 0x0C);
  temp_r4_3 = temp_r4_2 + 0xC000;
  *((s32 *) ((*(new_var6 = &temp_r6[1])) + 0x7C)) = (*((s32 *) (temp_r6[0] + 0x7C))) + ((sub_080C31E0(temp_r4_3, *inline_fn2(0x08671BFC)) >> 8) << 0x0C);
  temp_r4_4 = ((0x900000 - ((*((s32 *) (((u8 *) temp_r7) + 0x0C))) + ((sub_080C31E0(temp_r4_3, *new_var7) >> 8) << 0x0C))) >> 6) >> 2;
new_var7 = 0;
  var_r2_2 = (sub_080C2F4C(0x03100000 - (temp_r4_4 * temp_r4_4)) << 0x10) >> 8;
  if ((*((s32 *) (((u8 *) temp_r7) + 8))) > (*((s32 *) ((temp_r0_2 = *new_var6) + 0x6C))))
  {
    var_r2_2 = 0 - var_r2_2;
  }
  temp_r4_2 = sub_08005910(temp_r4_4 << 8, var_r2_2);
  sp4 = temp_r4_2;
  *((s32 *) (temp_r6[2] + 0x6C)) = (*((s32 *) ((*new_var6) + 0x6C))) + ((sub_080C31E0(temp_r4_2 + 0x4000, *inline_fn2(0x08671BFC)) >> 8) * 0x1800);
  *((s32 *) (temp_r6[2] + 0x7C)) = (*((s32 *) ((*new_var6) + 0x7C))) + ((sub_080C31E0(temp_r4_2, *inline_fn2(0x08671BFC)) >> 8) * 0x1800);
  *((s32 *) ((new_var4 + new_var5) + 0x8C)) = sp8;
  *((s32 *) ((*new_var6) + 0x8C)) = inline_fn(var_r9, sp4);
}
