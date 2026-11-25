struct A
{
  u16 f00;
  u16 f02;
  u32 f04;
  u8 _08[4];
  u32 f0C;
  s16 f10;
  s16 f12;
  u16 *f14;
};
s32 sub_080C36E4(s32, s16);
inline int inline_fn(s32 arg0)
{
  return arg0 * 2;
}

inline u16 *inline_fn2(s32 arg0, char arg1, int arg2, s32 arg3, s32 arg4)
{
  return (u16 *) ((arg0 + (((*((u16 *) (inline_fn(arg1) + arg2))) * 0x10) + arg3)) + (arg4 & 3));
}

inline u16 *inline_fn23(u16 *arg0)
{
  return arg0;
}

inline int inline_fn234(struct A *arg0, s32 arg1)
{
  return arg0->f10 * arg1;
}

inline u16 inline_fn2345(struct A *arg0)
{
  return arg0->f00;
}

inline int inline_fn23456(s32 arg0, int arg1)
{
  return arg0 - arg1;
}

inline int inline_fn234567(s32 arg0, s32 arg1)
{
  return (arg0 * 2) + arg1;
}

inline int inline_fn2345678(s32 arg0, s32 arg1)
{
  return arg0 + arg1;
}

void sub_08004484(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  struct A *a = arg0;
  volatile char pad;
  u16 new_var13;
  int new_var15;
  s32 sp4;
  int new_var6;
  unsigned short spC;
  s32 sp8;
  u16 *new_var2;
  s32 sp10;
  s32 sp14;
  s32 sp0;
  volatile int sp18;
  s32 sp1C;
  s32 sp20;
  s32 sp24;
  s32 sp28;
  s32 sp2C;
  unsigned int sp30;
  struct A *new_var;
  s16 temp_r4;
  s16 temp_r4_2;
  s16 temp_r4_3;
  s16 temp_r4_4;
  s32 temp_r1_2;
  s32 temp_r2;
  int new_var3;
  s32 temp_r2_2;
  s32 temp_r8;
  s32 temp_r8_2;
  s32 temp_r9;
  unsigned long new_var16;
  s32 temp_r9_2;
  s32 var_r2;
  s32 var_r2_3;
  u16 *new_var7[2];
  int new_var5;
  int new_var11;
  s32 var_r2_4;
  int new_var14;
  s32 var_r3;
  unsigned int new_var4;
  s32 var_r3_2;
  s32 var_r3_3;
  s32 var_r4;
  int new_var10;
  s32 new_var9;
  int new_var8;
  s32 var_r5;
  s32 var_r5_2;
  u16 temp_r1;
  u16 var_r0;
  u16 var_r0_2;
  u16 var_r10;
  u16 var_r10_2;
  int new_var12;
  new_var9 = arg1;
  sp0 = new_var9;
  sp4 = arg3;
  if (a->f00 & 0x100)
  {
    temp_r1_2 = 0x10 << (((u16) a->f02) >> 0xE);
    sp8 = inline_fn23456(temp_r1_2, 1);
    sp10 = (s32) (sp18 = a->f04);
    var_r3_2 = arg2;
    if (var_r3_2 > arg4)
    {
      return;
    }
    new_var15 = 3;
    loop_4:
    var_r2_3 = var_r3_2 >> 2;

    if (inline_fn2345(a) & 0x200)
    {
      temp_r4_3 = a->f12;
      sp30 = var_r3_2;
      var_r2_3 = sub_080C36E4(var_r2_3, temp_r4_3);
      if (var_r2_3 < 0)
      {
        if (1)
        {
          var_r2_3 += temp_r4_3;
        }
      }
      var_r10_2 = 1;
    }
    else
    {
      var_r10_2 = 0;
      if ((var_r2_3 >= 0) && (var_r2_3 < ((s32) a->f12)))
      {
        var_r10_2 = 1;
      }
    }
    temp_r8_2 = inline_fn234(a, var_r2_3);
    temp_r8_2 = temp_r8_2 * 2;
    temp_r8_2 = inline_fn2345678((s32) a->f0C, temp_r8_2);
    var_r5_2 = spC * (var_r3_2 & sp8);
    temp_r9_2 = sp14 + var_r5_2;
    sp18 = var_r3_2 & new_var15;
    var_r5_2 = sp0;
    sp2C = var_r3_2 + 1;
    new_var5 = 4;
    new_var12 = var_r5_2;
    if (new_var12 <= sp4)
    {
      var_r3_3 = sp18 * new_var5;
      new_var11 = temp_r1_2 - 1;
      new_var8 = var_r10_2 != 0;
      new_var6 = temp_r8_2;
      do
      {
        ;
        if (new_var8)
        {
          temp_r2_2 = var_r5_2 >> 2;
          new_var = a;
          if (inline_fn2345(new_var) & 0x400)
          {
            temp_r4_4 = a->f10;
            sp30 = var_r3_3;
            var_r2_3 = sub_080C36E4(temp_r2_2, temp_r4_4);
            var_r2_4 = var_r2_3;
            var_r4 = var_r2_4;
            if (var_r4 < 0)
            {
              var_r2_4 += temp_r4_4;
            }
            var_r0_2 = *((u16 *) ((var_r3_3 + (((new_var13 = *((u16 *) inline_fn234567(var_r2_4, new_var6))) * 0x10) + sp10)) + (var_r5_2 & 3)));
          }
          else
            if ((temp_r2_2 >= 0) && (temp_r2_2 < ((s32) a->f10)))
          {
            var_r0_2 = *(new_var7[0] = inline_fn2(var_r3_3, temp_r2_2, new_var6, sp10, var_r5_2));
          }
          else
          {
            var_r0_2 = 0;
          }
        }
        *((u16 *) ((var_r5_2 & new_var11) + temp_r9_2)) = var_r0_2;
        var_r5_2 += 2;
      }
      while (var_r5_2 <= sp4);
      var_r3_2 = sp2C;
    }
    if (var_r3_2 <= arg4)
    {
      goto loop_4;
    }
    spC = temp_r1_2;
    return;
    return;
  }
  sp14 = (s32) a->f14;
  sp18 = (s32) a->f04;
  temp_r1 = a->f02;
  if (temp_r1 & 0x4000)
  {
    sp1C = 5;
    if (temp_r1 & 0x8000)
    {
      var_r4 = 4;
      sp20 = 6;
      sp20 = var_r4;
    }
  }
  else
  {
    sp1C = 6;
    temp_r4_2 = temp_r1;
    temp_r4_2 = temp_r4_2 & 0x8000;
    sp20 = 6;
    if (temp_r4_2)
    {
      if (a || var_r3_2)
      {
        var_r4 = 5;
        sp20 = var_r4;
      }
      else
      {
        var_r4 = 5;
        sp20 = var_r4;
      }
    }
  }
  var_r3 = arg2;
  sp28 = (s32) a->f0C;
  loop_55:
  if (var_r3 > arg4)
  {
    goto dummy_label_191087;
    dummy_label_191087:
    ;

    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
    ;
  }

  new_var10 = 3;
  sp24 = (0x20 & var_r3) >> sp20;
  var_r2 = var_r3 >> 2;
  if ((temp_r4_3 = inline_fn2345(a)) & 0x200)
  {
    temp_r4 = a->f12;
    sp30 = var_r3;
    var_r2 = sub_080C36E4(var_r2, temp_r4);
    if (var_r2 < 0)
    {
      var_r2 += temp_r4;
    }
    var_r10 = 1;
  }
  else
  {
    var_r10 = 0;
    if ((var_r2 >= 0) && (var_r2 < ((s32) a->f12)))
    {
      if (var_r5_2)
      {
        var_r10 = 1;
      }
      else
      {
        var_r10 = 1;
      }
    }
  }
  temp_r8 = sp28 + ((a->f10 * var_r2) * 2);
  sp10 = var_r3 & new_var10;
  var_r5 = sp0;
  sp2C = var_r3 + 1;
  if (var_r5 <= sp4)
  {
    new_var4 = sp10 * 8;
    temp_r9 = new_var4;
    do
    {
      new_var7[1] = (u16 *) (((sp14 + ((sp24 + ((0x20 & var_r5) >> sp1C)) << 0xB)) + (new_var12 = (var_r3 & 0x1F) << 6)) + ((var_r5 & 0x1F) * 2));
      new_var3 = new_var10;
      new_var2 = new_var7[1];
      new_var8 = 2;
      if (var_r10 == 0)
      {
        *new_var7[1] = var_r10;
      }
      else
      {
        temp_r2 = var_r5 >> 2;
        if (a->f00 & 0x400)
        {
          temp_r4_2 = a->f10;
          var_r2_3 = sub_080C36E4(temp_r2, temp_r4_2);
          sp30 = var_r3;
          var_r2_3 = var_r2_3;
          if (var_r2_3 < 0)
          {
            var_r2_3 = var_r2_3 + temp_r4_2;
          }
          temp_r4 = inline_fn234567(var_r2_3, temp_r8);
          new_var13 = *((u16 *) temp_r4);
          new_var2 = (u16 *) inline_fn234567(var_r5 & new_var3, (sp18 + (new_var13 << 5)) + temp_r9);
          var_r0 = *new_var2;
        }
        else
          if ((temp_r2 >= 0) && (temp_r2 < ((s32) a->f10)))
        {
          do
          {
            new_var14 = temp_r2 * 2;
            new_var16 = new_var14 + temp_r8;
            var_r0 = *((u16 *) (((new_var16 * 0) + ((((*((u16 *) new_var16)) << 5) + sp18) + temp_r9)) + ((var_r5 & new_var10) * new_var8)));
          }
          while (0);
        }
        else
        {
          var_r0 = 0;
        }
        *inline_fn23(new_var2) = var_r0;
      }
      var_r5 += 1;
    }
    while (var_r5 <= sp4);
  }
  var_r3 = sp2C;
  goto loop_55;
}

