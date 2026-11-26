extern s32 sub_080059DC(s32, s32);
extern void sub_080146D0();
/* Grows the polar vector held at out+0x10/+0x14 by step, clamps its radius to
 * limit and rebuilds x/y from angle; returns 1 when the limit is reached. */
s32 sub_08014A34(void *out, s32 angle, s32 step, s32 limit)
{
  s32 radius = sub_080059DC(*((s32 *) (((u8 *) out) + 0x10)), *((s32 *) (((u8 *) out) + 0x14)));
  s32 target = radius;
  s32 result;
  target = target + step;
  if (target < limit)
  {
    sub_080146D0(out, angle);
    result = 0;
  }
  else
  {
    target = limit;
    sub_080146D0(out, angle, target);
    result = 1;
  }
  return result;
}

s32 sub_08014A04(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 sub_08005820(s32);
extern s32 signOf(s32);
void sub_080149A4(void *arg0, void *arg1, u16 *arg2, u16 arg3, s32 arg4);
