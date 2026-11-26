typedef s32 M2C_UNK;
extern M2C_UNK sub_080ACCA4(s32, s32, void *, void *);
extern M2C_UNK sub_080AC9B4(u8, void *);
extern M2C_UNK sub_080C31E4(void *, void *, s32);
void sub_080AC170(void *arg0)
{
  void *temp_r4;
  s32 temp_r6;
  s32 var_r12;
  s32 *var_r5;
  void **var_r4;
  s32 *var_r3;
  s32 *root;

  temp_r6 = *((s32 *) (((s8 *) arg0) + 0x38));
  temp_r4 = *((void **) (((s8 *) arg0) + 0x3C));
  sub_080AC9B4(*((u8 *) (((s8 *) temp_r4) + 0x244)), temp_r4 + 0x68);
  sub_080ACCA4(0, temp_r6, temp_r4, temp_r4 + 0x98);
  sub_080ACCA4(1, temp_r6, temp_r4, temp_r4 + 0x98);
  var_r12 = 1;
  root = (s32 *) 0x08102214;
  var_r5 = root;
  var_r4 = (void **) (temp_r4 + 0xA4);
  var_r3 = root;
  do
  {
    s32 *obj;
    s32 val;
    s32 delta;

    obj = *var_r4;
    val = obj[0x5C / 4];
    delta = var_r3[1];
    obj[0x5C / 4] = val + delta;
    if (delta > 0)
    {
      s32 *obj2;
      s32 val;
      s32 limit;

      obj2 = *var_r4;
      val = obj2[0x5C / 4];
      limit = var_r3[0];
      if (val > limit)
      {
        obj2[0x5C / 4] = limit;
        goto next;
      }
    }
    if (var_r3[1] < 0)
    {
      s32 *obj2;
      s32 val;
      s32 limit;

      obj2 = *var_r4;
      val = obj2[0x5C / 4];
      limit = *var_r5;
      if (val < limit)
      {
        obj2[0x5C / 4] = limit;
        goto next;
      }
    }
    else
    {
      goto not_clamped;
    }
    goto not_clamped;
  next:
    goto cont;
  not_clamped:
    var_r12 = 0;
  cont:
    var_r5 += 2;
    var_r4 += 1;
    var_r3 += 2;
  }
  while (var_r3 <= root + 2);
  if (var_r12 != 0)
  {
    s32 *lit;
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    lit = (s32 *) 0x08671BB0;
    sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *lit);
  }
}
