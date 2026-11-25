typedef s32 M2C_UNK;
extern M2C_UNK sub_080ACCA4(s32, s32, void *, void *);
extern M2C_UNK sub_080AC9B4(u8, void *);
extern M2C_UNK sub_080C31E4(void *, void *, s32);
void sub_080AC170(void *arg0)
{
  u32 new_var;
  void *var_r3;
  s32 *var_r5;
  s32 *root;
  s32 new_var3;
  u32 temp_r2;
  s32 temp_r6;
  s32 var_r12;
  s32 var_r1;
  void **var_r4;
  void *temp_r0;
  void *temp_r4;
  temp_r6 = *((s32 *) (((s8 *) arg0) + 0x38));
  temp_r4 = *((void **) (((s8 *) arg0) + 0x3C));
  sub_080AC9B4(*((u8 *) (((s8 *) temp_r4) + 0x244)), temp_r4 + 0x68);
  sub_080ACCA4(0, temp_r6, temp_r4, temp_r4 + 0x98);
  sub_080ACCA4(1, temp_r6, temp_r4, temp_r4 + 0x98);
  var_r12 = 1;
  root = (s32 *) 0x08102214;
  var_r5 = root;
  var_r4 = temp_r4 + 0xA4;
  var_r3 = root;
  do
  {
    temp_r0 = *var_r4;
    new_var3 = *((s32 *) (((s8 *) temp_r0) + 0x5C));
    temp_r2 = *((u32 *) (((s8 *) var_r3) + 4));
    *((s32 *) (((s8 *) temp_r0) + 0x5C)) = (s32) (new_var3 + temp_r2);
    if ((((s32)temp_r2 > 0) && (((s32) (*((vu32 *) (((s8 *) (*var_r4)) + 0x5C)))) > (var_r1 = *((s32 *) (((s8 *) var_r3) + 0))))) || ((((s32)temp_r2 < 0) && (((s32) (*((vu32 *) (((s8 *) (*var_r4)) + 0x5C)))) < (var_r1 = *var_r5)))))
    {
      *((vu32 *) (((s8 *) (*var_r4)) + 0x5C)) = var_r1;
    }
    else
    {
      var_r12 = 0;
    }
    var_r5 += 2;
    var_r4 += 1;
    var_r3 += 8;
  }
  while ((s8 *)var_r3 <= ((s8 *) root) + 8);
  if (var_r12 != 0)
  {
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    new_var = 0x08671BB0;
    sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *((s32 *) new_var));
  }
}
