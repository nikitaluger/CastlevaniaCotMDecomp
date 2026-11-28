void initCrossfadeGfxState(void);
void sub_080C31E8(void *, void *, s32, s32);

/* Decelerate the vertical speed by 0x1000 per tick; when it reaches zero,
 * stop the actor's horizontal and vertical motion, refresh its pose and
 * advance to the next script step. */
void sub_0809F254(void *arg0)
{
    s32 speed;
    s32 *stepTable;
    speed = *(s32 *)((u8 *)arg0 + 0x5C) + 0xFFFFF000;
    *(s32 *)((u8 *)arg0 + 0x5C) = speed;
    if (speed <= 0)
    {
        *(u8 *)((u8 *)arg0 + 0x70) = 0;
        *(u8 *)((u8 *)arg0 + 0x74) = 0;
        initCrossfadeGfxState();
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
        stepTable = (s32 *)0x08671BD0;
        sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0, *stepTable);
    }
}
