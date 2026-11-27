extern s32 setAnimationFrame(s32, s32, s32, s32);
extern s32 sub_08014A04(s32, s32, s32, s32, s32);
extern s32 getSpriteFacingSign(s32);
extern s32 sub_0800583C(s32);
extern void randomizeLaunchOffsets(void *, void *);
extern void sub_08014B1C(s32, s32, s32, s32);
extern void setSpriteFlip(s32, s32);
extern void _call_via_r2(void *, void *, s32);

void sub_080253A4(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *motion = *(u8 **)(entity + 0x3c);
    u8 *animState = motion + 0x34;
    u8 *steer = motion + 0x48;
    s32 targetX;
    s32 targetY;
    u32 coordBase;
    u32 coordOffset;

    setAnimationFrame((s32)sprite, (s32)animState, 0, 1);
    coordBase = 0x02025FF0;
    coordOffset = 0x1728;
    targetX = *(s32 *)(coordBase + coordOffset) + *(s32 *)(steer + 8);
    coordOffset = 0x172C;
    targetY = *(s32 *)(coordBase + coordOffset) + *(s32 *)(steer + 0x0C);

    if (sub_08014A04((s32)motion, targetX, targetY, 0x100000, 0x100000) == 1)
    {
        s32 counter = (s16)(*(u16 *)(steer + 0x12) - 1);
        *(u16 *)(steer + 0x12) = counter;
        if (counter >= 0)
        {
            randomizeLaunchOffsets(motion + 0x50, motion + 0x54);
        }
        else
        {
            if (getSpriteFacingSign((s32)sprite) > 0)
                *(s32 *)(steer + 8) = -0x300000;
            else
                *(s32 *)(steer + 8) = 0x300000;
            *(s32 *)(steer + 0x0C) = sub_0800583C(0x200000) - 0x300000;
            *(u16 *)(steer + 0x10) = 0;
            {
                s16 scriptIndex = *(s16 *)(entity + 0x22);
                *(u8 *)(entity + scriptIndex * 2 + 0x19) = 0;
                {
                    s32 *callbacks = (s32 *)0x08671BB0;
                    _call_via_r2(entity + 0x18, entity + 0x22, *callbacks);
                }
            }
        }
    }
    else
    {
        sub_08014B1C((s32)entity, (s32)(entity + 0x18), targetX, targetY);
        setSpriteFlip((s32)sprite, *(s32 *)(steer + 0x1C));
    }
}
