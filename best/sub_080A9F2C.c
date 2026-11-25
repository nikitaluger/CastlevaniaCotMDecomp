extern void sub_0800168C(u8 *, s32, s32, s32);
extern u32 sub_08005820(u32);
extern u32 sub_0805FAEC(u32, u32);
extern void sub_080C31E0(u8 *, u32);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern u32 D_02027860;
extern u8 D_0810212C[];
extern u32 D_08102130[];
extern u32 D_08102134[];
extern u32 D_08671BB0;
struct A
{
  u8 pad0[2];
  u16 unk2;
  u8 pad4[0x10];
  u32 unk14;
  u8 unk18;
  u8 unk19;
  u8 pad1A[8];
  s16 unk22;
  u32 unk24;
  u8 pad28[0x14];
  u32 unk3C;
  u8 pad40[0xC];
  u32 unk4C;
};
void sub_080A9F2C(struct A *arg0)
{
  s32 sp0;
  int new_var3;
  u8 *sp4;
  u8 *sp8;
  u8 *spC;
  u8 *sp10;
  u8 *sp14;
  u8 *sp18;
  u32 *new_var2;
  u8 *sp1C;
  u8 *sp20;
  u8 *sp24;
  u8 *sp28;
  s32 sp2C;
  s32 var_r4;
  u8 *var_r5;
  s8 var_r6;
  u8 *temp_r0;
  u32 var_r9;
  s32 var_r3;
  int new_var;
  u8 *temp_r2;
  u8 *var_r4_2;
  u8 *var_r5_2;
  u8 *var_r10_2;
  u8 *var_r8;
  u32 temp_r0_4;
  u8 *temp_r0_2;
  u8 *temp_r0_3;
  u8 *temp_r1;
  sub_0800168C((u8 *) arg0, 0, 0xC8, 0);
  temp_r1 = (u8 *) arg0->unk3C;
  if (temp_r1 == NULL)
  {
    sub_080C31E0((u8 *) arg0, arg0->unk24);
    return;
  }
  temp_r0 = temp_r1 + 0x48;
  *((u16 *) (temp_r1 + 0x1C)) = 0x5F;
  var_r9 = 0;
  sp4 = ((u8 *) arg0) + 0x18;
  spC = ((u8 *) arg0) + 0x22;
  temp_r0_2 = temp_r1 + 0x60;
  sp8 = temp_r0_2;
  temp_r2 = temp_r1 + 0x78;
  new_var = sub_08005820(0x80) + 0x80;
  sp1C = temp_r2;
  temp_r0_3 = temp_r0_2 + 8;
  sp14 = temp_r0_3;
  sp20 = temp_r2 + 0x18;
  sp10 = temp_r0_3 + 0x48;
  var_r3 = 0;
  sp18 = temp_r1 + 0xC0;
  do
  {
    sp0 = D_0810212C[(arg0->unk4C * 2) + var_r9];
    *((u32 *) ((temp_r0 + 0x58) + (var_r9 * 4))) = 0x3000;
    var_r6 = 0;
    var_r3 = var_r9 * 8;
    var_r5 = temp_r0 + var_r3;
    var_r4 = var_r3;
    loop_4:
    if (var_r6 != 1)
    {
      sp2C = var_r3;
      temp_r0_4 = sub_0805FAEC(D_02027860, 0x1A2);
      *((u32 *) var_r5) = temp_r0_4;
      *((u32 *) ((temp_r0 + 0x28) + var_r4)) = D_08102130[var_r3 + (arg0->unk4C * 0x10)];
      *((u32 *) ((temp_r0 + 0x40) + var_r4)) = (new_var2 = D_08102134)[var_r3 + (arg0->unk4C * 0x10)];
      *((u8 *) (temp_r0_4 + 0x7C)) = (u8) sp0;
      *((u8 *) (temp_r0_4 + 0x80)) = var_r6;
    }

    var_r5 += 4;
    var_r4 += 4;
    var_r6 += 1;
    if (((u32) var_r6) <= 2U)
    {
      goto loop_4;
    }
    var_r3 += 0xC;
    var_r9 += 1;
  }
  while (var_r9 <= 1U);
  var_r9 = 0;
  sp24 = sp18;
  sp28 = sp10;
  var_r5_2 = sp20;
  var_r10_2 = sp14;
  var_r4_2 = sp1C;
  var_r8 = sp8;
  do
  {
    temp_r2 = var_r8 + 4;
    var_r8 = temp_r2;
    *((u32 *) (temp_r2 - 4)) = *((u32 *) var_r4_2);
    temp_r0_2 = var_r10_2 + 4;
    var_r10_2 = temp_r0_2;
    *((u32 *) (temp_r0_2 - 4)) = *((u32 *) var_r5_2);
    *((u32 *) sp28) = sub_08005820(0x200) + 0x200;
    sp28 += 4;
    *((u32 *) sp24) = new_var;
    sp24 += 4;
    var_r5_2 += 0xC;
    var_r4_2 += 0xC;
    var_r9 += 1;
  }
  while (var_r9 <= 1U);
  arg0->unk2 |= 0x1000;
  ((struct A *) (((u8 *) arg0) + (arg0->unk22 * 2)))->unk19 = 0;
  sub_080C31E4(sp4, spC, D_08671BB0);
  ((struct A *) (((u8 *) arg0) + (arg0->unk22 * 2)))->unk19 += 1;
  new_var3 = arg0->unk22 * 2;
  sub_080C31E0((u8 *) arg0, *((u32 *) (((*((u8 *) (sp4 + new_var3))) * 4) + arg0->unk14)));
}

