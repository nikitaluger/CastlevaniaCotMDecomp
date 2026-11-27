extern void sub_08005E80(s32);
extern void sub_08011528(void *, void *);
extern void *spawnBudgetedEffect(void *, s32);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;

/* Actor script step: when the linked body's animation has flag 0x02 set, spawn
 * two child objects (ids 0x1BC/0x1BD) that inherit a left/right direction,
 * clear the sprite highlight bit, play sound 0x180 and advance the script. */
void sub_080B2614(void *arg0)
{
    void *sprite;
    u8 *animData;
    void *childA;
    void *childB;
    s32 direction;
    s32 zero;
    u8 *highlight;
    u8 newHighlight;
    void **scriptTable;

    sprite = *(void **)((u8 *)arg0 + 0x38);
    animData = (u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x34;
    sub_08011528(sprite, animData);

    if (animData[0] & 2)
    {
        childA = spawnBudgetedEffect(arg0, 0x1BC);

        if (*(u16 *)(*(void **)(*(void **)((u8 *)arg0 + 0x28) + 0x38) + 2) & 0x10)
            direction = 1;
        else
            direction = -1;
        *(s32 *)((u8 *)childA + 0x4C) = direction;

        childB = spawnBudgetedEffect(arg0, 0x1BD);
        *(s32 *)((u8 *)childB + 0x4C) = *(s32 *)((u8 *)childA + 0x4C);

        highlight = (u8 *)sprite + 0x2A;
        newHighlight = *highlight & 0xBF;
        zero = 0;
        *highlight = newHighlight;

        sub_08005E80(0x180);
        *(s8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = (s8)zero;
        scriptTable = &gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptTable);
    }
}
