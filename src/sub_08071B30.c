void sub_080C31E4(void *, void *, s32);

/* Reset the global work-state block at 0x02025FF0+0x1800 (two 0xFFFF fields,
 * a counter and a set of flags), clear the actor's current script byte, then
 * dispatch the script callback through the pointer at 0x08671BB0. */
void sub_08071B30(void *arg0)
{
    u8 *actor = (u8 *)arg0;
    u8 *work = (u8 *)0x02025FF0;

    *(u32 *)(work + 0x1800) = 0x0000FFFF;
    *(u32 *)(work + 0x1804) = 0x0000FFFF;
    *(u32 *)(work + 0x1808) = 1;
    *(u32 *)(work + 0x180C) = 0;
    *(u32 *)(work + 0x1810) = 0;
    *(u32 *)(work + 0x1814) = 0;
    *(u32 *)(work + 0x1818) = 0;
    *(u32 *)(work + 0x181C) = 0;
    *(u32 *)(work + 0x1820) = 0;
    *(u32 *)(work + 0x1824) = 0;
    *(u32 *)(work + 0x1828) = 0;
    *(u32 *)(work + 0x182C) = 0;
    *(u32 *)(work + 0x1830) = 0;
    *(u32 *)(work + 0x1838) = 0;
    *(u32 *)(work + 0x183C) = 0;
    *(u32 *)(work + 0x1844) |= 0x02000000;

    {
        s16 scriptOffset = *(s16 *)(actor + 0x22);
        *(u8 *)(actor + scriptOffset * 2 + 0x19) = 0;
    }

    {
        s32 *callbackArg = (s32 *)0x08671BB0;
        sub_080C31E4(actor + 0x18, actor + 0x22, *callbackArg);
    }
}
