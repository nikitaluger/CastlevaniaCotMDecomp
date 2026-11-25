inline static s8 *inline_fn(void *arg0)
{
  return (s8 *) arg0;
}

static inline u32 andTwo(u16 v)
{
  u32 m = 2;
  m &= v;
  return m;
}

void sub_0807E8D0(void *arg0)
{
  u8 *temp_r7;
  u8 *temp_r5;
  u16 *temp_r0;
  s8 *new_var;
  u8 *new_var2;
  s32 temp_r2;
  s32 new_var3;
  s32 temp_r3;
  s32 var_r1;
  s32 var_r1_2;
  u16 temp_r1;
  u16 temp_r1_2;
  void *temp_r0_3;
  s32 temp_r0_2;
  s32 off18A8;
  u8 *pb;
  u8 *pb2;
  temp_r7 = *((u8 **) (inline_fn(arg0) + 0x6C));
  temp_r5 = temp_r7 + 4;
  temp_r0 = *((u16 **) (inline_fn(arg0) + 0x38));
  new_var = inline_fn(temp_r5);
  if (sub_0806D518(arg0, temp_r0, temp_r5) != 0)
  {
    return;
  }
  new_var3 = *((s32 *) (new_var + 0x48));
  temp_r2 = new_var3;
  if (((s32) temp_r2) <= 0xFF)
  {
    u8 *p1 = (u8 *) (*((u32 *) (new_var + 0x4C)));
    u8 *p2 = ((u8 *) temp_r7) + 0x54;
    u8 byte1 = p1[1];
    u8 byte2 = *p2;
    if (byte1 != byte2)
    {
      *((s32 *) (inline_fn(temp_r5) + 0x48)) = temp_r2 + 0x100;
    }
  }
  temp_r0_2 = (*((s32 *) (inline_fn(temp_r5) + 0x48))) + 1;
  new_var2 = new_var + 8;
  *((s32 *) (inline_fn(temp_r5) + 0x48)) = temp_r0_2;
  if (((s32) temp_r0_2) <= 0xFF)
  {
    temp_r0_3 = *((void **) (inline_fn(temp_r5) + 0x4C));
    sub_08072334(new_var, *((s32 *) (inline_fn(temp_r0_3) + 0x0C)), *((s32 *) (inline_fn(temp_r0_3) + 0x10)), temp_r5 + 0x40);
  }
  sub_080722E0(new_var, *((u8 *) (((u8 *) temp_r5) + 0x44)));
  var_r1 = (*((s32 *) new_var2)) * ((*((s32 *) (((u8 *) temp_r5) + 0x40))) >> 8);
  if (var_r1 < 0)
  {
    var_r1 += 0xFF;
  }
  temp_r3 = (*((s32 *) new_var)) + (var_r1 >> 8);
  *((s32 *) new_var) = temp_r3;
  var_r1_2 = (*((s32 *) (new_var + 0x0C))) * ((*((s32 *) (((u8 *) temp_r5) + 0x40))) >> 8);
  if (var_r1_2 < 0)
  {
    var_r1_2 += 0xFF;
  }
  *((s32 *) (new_var + 0x04)) += var_r1_2 >> 8;
  temp_r1 = *((u16 *) (((u8 *) (*((u32 *) (((u8 *) temp_r5) + 0x2C)))) + 0x14));
  off18A8 = 0x18A8;
  pb = (u8 *) 0x02025FF0;
  if (((temp_r1 & 1) && (andTwo(temp_r1) == 0)) || ((temp_r1_2 = sub_08007DD8(((*((u8 *) (pb + off18A8))) << 6) + 0x02023130, temp_r3)) != 0))
  {
    sub_0808DBF8(*((s32 *) new_var), *((s32 *) (new_var + 4)), 0);
    goto block_18;
  }
  *((u16 *) (((u8 *) (*((u32 *) (((u8 *) temp_r5) + 0x2C)))) + 0x14)) = temp_r1_2;
  *temp_r0 = *((u16 *) (pb + 0x18C2));
  sub_08003740(temp_r5 + 0x1C);
  pb2 = (u8 *) 0x02025FF0;
  sub_0806D588(temp_r0, new_var);
  if (((*((u8 *) (pb2 + 0x173A))) == 0x1C) || (((*((u8 *) (pb2 + 0x14ED))) == 0) && ((*((s32 *) (pb2 + 0x10))) != 0)))
  {
 do { block_18: sub_080C31E0(arg0, *((s32 *) (inline_fn(arg0) + 0x24))); return; } while (0);
  }
  sub_0806D2F8(arg0, temp_r0);
}
