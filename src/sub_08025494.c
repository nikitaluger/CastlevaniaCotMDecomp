/* Steer an entity toward a moving target, then signal completion once it arrives:
 * refresh its animation, and either clear a script sub-state byte and fire the
 * arrival callback, or turn toward the target and latch the sub-state flag. */
extern s32 sub_08011368(s32, s32, s32, s32);
extern s32 sub_08014A04(s32, s32, s32, s32, s32);
extern s32 sub_08014A6C(s32, s32, s32, s32);
extern void sub_08014B1C(s32, s32, s32, s32);
extern void _call_via_r3(void *, void *, s32, s32);

void sub_08025494(void *arg0)
{
    s32 *sprite;
    u8 *motion;
    u8 *animState;
    u8 *steer;
    s32 targetX;
    s32 targetY;
    u8 *entity = (u8 *)arg0;
    u32 coordBase;
    u32 coordOffset;

    sprite = *(s32 **)(entity + 0x38);
    motion = *(u8 **)(entity + 0x3C);
    animState = motion + 0x34;
    steer = motion + 0x48;
    sub_08011368((s32)sprite, (s32)animState, 0, 1);
    coordBase = 0x02025FF0;
    coordOffset = 0x1728;
    targetX = *(s32 *)(coordBase + coordOffset) + *(s32 *)(steer + 8);
    coordOffset = 0x172C;
    targetY = *(s32 *)(coordBase + coordOffset) + *(s32 *)(steer + 0x0C);

    if (*(s16 *)(steer + 0x10) == 1)
    {
        if (sub_08014A6C((s32)motion, *(s32 *)(steer + 0x1C), 0x1800, 0) == 1)
        {
            s16 scriptIndex = *(s16 *)(entity + 0x22);
            *((u8 *)entity + scriptIndex * 2 + 0x19) = 0;
            {
                s32 *callbacks = (s32 *)0x08671BD0;
                _call_via_r3(entity + 0x18, entity + 0x22, 3, *callbacks);
            }
        }
    }
    else
    {
        if (sub_08014A04((s32)motion, targetX, targetY, 0x100000, 0x100000) == 1)
        {
            *(s16 *)(steer + 0x10) = 1;
        }
        else
        {
            sub_08014B1C((s32)motion, (s32)(motion + 0x60), targetX, targetY);
        }
    }
}
