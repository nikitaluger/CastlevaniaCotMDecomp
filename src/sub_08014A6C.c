s32 fixedPointDistance(s32, s32);
void sub_080146D0(void *, s32, s32);

/* Shrinks the polar vector held at out+0x10/+0x14 by step, clamps its radius to
 * limit and rebuilds x/y from angle; returns 1 when the limit is reached. */
s32 sub_08014A6C(void *out, s32 angle, s32 step, s32 limit)
{
    s32 radius = fixedPointDistance(*(s32 *)((u8 *)out + 0x10), *(s32 *)((u8 *)out + 0x14));
    s32 target = radius;
    target = target - step;
    if (target <= limit)
    {
        target = limit;
        sub_080146D0(out, angle, target);
        return 1;
    }
    sub_080146D0(out, angle, target);
    return 0;
}
