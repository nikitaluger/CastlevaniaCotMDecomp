s32 sub_080C36E0();
u32 sub_080C389C(u32 arg0, u32 arg1)
{
  u32 var_r0;
  u32 var_r1;
  u32 var_r2;
  u32 t;
  if (arg1 == 0)
  {
    sub_080C36E0();
    return 0;
  }
  var_r0 = arg0;
  var_r1 = arg1;
  t = 1;
  if (var_r0 < var_r1)
  {
    return var_r0;
  }
  t = var_r0;
  t = 0x80000000U;
  var_r0 = 0x10000000U;
  while ((var_r1 < var_r0) && (var_r1 < t))
  {
    var_r1 <<= 4;
    t <<= 4;
  }

  while ((var_r1 < t) && (var_r0 = var_r1 < t))
  {
    var_r1 <<= 1;
    t <<= 1;
  }

  t = 1;
  t = var_r1 >> t;
  var_r2 = 0;
  if (t >= var_r1)
  {
    var_r0 -= var_r1;
  }
  if (var_r0 >= t)
  {
    var_r0 -= t;
  }
  return var_r0;
}

