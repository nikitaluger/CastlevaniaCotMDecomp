typedef s32 M2C_UNK;
struct D_02025FF0_S
{
  u8 _0[0x14ED];
  u8 f14ED;
  u8 _1[0x173A - 0x14EE];
  u8 f173A;
  u8 _2[0x18C2 - 0x173B];
  u16 f18C2;
};
extern struct D_02025FF0_S D_02025FF0;
M2C_UNK sub_08003740(void *, u16 *);
M2C_UNK sub_0806D2F8(void *, u16 *);
s32 sub_0806D518(void *, u16 *, void *);
M2C_UNK sub_0806D588(u16 *, void *);
M2C_UNK sub_0806E114(s32, s32, s32, s32);
M2C_UNK sub_080722E0(void *, u8);
M2C_UNK sub_08072334(void *, s32, s32, void *);
M2C_UNK sub_0808DBF8(s32, s32, s32);
M2C_UNK sub_080C31E0(void *, s32);
void sub_08077932(void *arg0)
{
  s32 temp_r0_2;
  s32 temp_r0_4;
  s32 temp_r0_5;
  s32 temp_r1_2;
  s32 temp_r2;
  s32 temp_r3;
  s32 var_r1;
  s32 var_r1_2;
  void *new_var;
  s8 *new_var4;
  void *temp_r0_3;
  void *temp_r4;
  void *temp_r6;
  s8 *new_var2;
  s16 new_var3;
  u16 *temp_r0;
  u16 temp_r2_2;
  u8 temp_r1;
  temp_r6 = *((void **) (((s8 *) arg0) + 0x6C));
  temp_r4 = temp_r6 + 4;
  temp_r0 = *((u16 **) (((s8 *) arg0) + 0x38));
  new_var4 = ((s8 *) temp_r4) + 0x54;
  if (sub_0806D518(arg0, temp_r0, temp_r4) != 0)
  {
    return;
  }
  temp_r2 = *((s32 *) (((s8 *) temp_r4) + 0x48));
  if ((temp_r2 <= 0xFF) && ((*((u8 *) (((s8 *) (*((void **) (((s8 *) temp_r4) + 0x4C)))) + 1))) != (*((u8 *) (((s8 *) temp_r6) + 0x54)))))
  {
    *((s32 *) (((s8 *) temp_r4) + 0x48)) = (s32) (temp_r2 + 0x100);
  }
  *((s32 *) (((s8 *) temp_r4) + 0x58)) = (s32) (*((s32 *) (((s8 *) temp_r4) + 0x54)));
  *((s32 *) new_var4) = (s32) (*((u8 *) (((s8 *) temp_r4) + 0x44)));
  temp_r0_2 = (*((s32 *) (((s8 *) temp_r4) + 0x48))) + 1;
  *((s32 *) (((s8 *) temp_r4) + 0x48)) = temp_r0_2;
  new_var2 = ((s8 *) temp_r4) + 0x54;
  if (temp_r0_2 <= 0xFF)
  {
    temp_r0_3 = *((void **) (((s8 *) temp_r4) + 0x4C));
    sub_08072334(temp_r4, *((s32 *) (((s8 *) temp_r0_3) + 0xC)), *((s32 *) (((s8 *) temp_r0_3) + 0x10)), temp_r4 + 0x40);
  }
  temp_r1 = *((u8 *) (((s8 *) temp_r4) + 0x44));
  if (((*((s32 *) new_var2)) == temp_r1) || ((*((s32 *) (((s8 *) temp_r4) + 0x58))) == temp_r1))
  {
    temp_r0_4 = (*((s32 *) (((s8 *) temp_r4) + 0x40))) + 0x4000;
    *((s32 *) (((s8 *) temp_r4) + 0x40)) = temp_r0_4;
    if (temp_r0_4 > 0x80000)
    {
      *((s32 *) (((s8 *) temp_r4) + 0x40)) = 0x80000;
    }
  }
  else
  {
    temp_r0_5 = (*((s32 *) (((s8 *) temp_r4) + 0x40))) + 0xFFFFC000;
    *((s32 *) (((s8 *) temp_r4) + 0x40)) = temp_r0_5;
    if (temp_r0_5 <= 0x3FFF)
    {
      *((s32 *) (((s8 *) temp_r4) + 0x40)) = 0x4000;
    }
  }
  sub_080722E0(temp_r4, *((u8 *) (((s8 *) temp_r4) + 0x44)));
  var_r1 = (*((s32 *) (((s8 *) temp_r4) + 8))) * (((s32) (*((s32 *) (((s8 *) temp_r4) + 0x40)))) >> 8);
  if (var_r1 < 0)
  {
    var_r1 += 0xFF;
  }
  temp_r3 = (*((s32 *) (((s8 *) temp_r6) + 4))) + (var_r1 >> 8);
  *((s32 *) (((s8 *) temp_r6) + 4)) = temp_r3;
  var_r1_2 = (*((s32 *) (((s8 *) temp_r4) + 0xC))) * (((s32) (*((s32 *) (((s8 *) temp_r4) + 0x40)))) >> 8);
  if (var_r1_2 < 0)
  {
    var_r1_2 += 0xFF;
  }
  temp_r1_2 = (*((s32 *) (((s8 *) temp_r4) + 4))) + (var_r1_2 >> 8);
  *((s32 *) (((s8 *) temp_r4) + 4)) = temp_r1_2;
  temp_r2_2 = *((u16 *) (((s8 *) (*((void **) (((s8 *) temp_r4) + 0x2C)))) + 0x14));
  if ((1 & temp_r2_2) && (!(2 & temp_r2_2)))
  {
    sub_0808DBF8(temp_r3, temp_r1_2, 0);
  }
  *((u16 *) (((s8 *) (*((void **) (((s8 *) temp_r4) + 0x2C)))) + 0x14)) = 0U;
  *temp_r0 = D_02025FF0.f18C2;
  if (!((*((s32 *) (((s8 *) temp_r4) + 0x48))) & 3))
  {
    sub_0806E114(*((s32 *) (((s8 *) arg0) + 0x28)), 0xA, *((s32 *) (((s8 *) temp_r6) + 4)), *((s32 *) (((s8 *) temp_r4) + 4)));
  }
  sub_08003740(temp_r4 + 0x1C, temp_r0);
  sub_0806D588(temp_r0, temp_r4);
  if ((D_02025FF0.f173A == 0x1C) || ((D_02025FF0.f14ED == 0) && ((*((s32 *) (((s8 *) (&D_02025FF0)) + 0x10))) != 0)))
  {
    sub_080C31E0(arg0, *((s32 *) (((s8 *) arg0) + 0x24)));
    return;
  }
  sub_0806D2F8(arg0, temp_r0);
}

