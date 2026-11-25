extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Reset the entity's +0x40 flag and +0x3C state byte, clear then bump the
 * current script-step byte, advance the step and dispatch the new handler. */
void sub_0805B358(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *stepCursor;
    const u32 *scriptTable;
    *(u8 *)(self + 0x40) = 0;
    *(u8 *)(self + 0x3C) = 1;
    *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
    scriptTable = (const u32 *)0x08671BB0;
    stepCursor = self + 0x18;
    sub_080C31E4(stepCursor, self + 0x22, *scriptTable);
    *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) += 1;
    stepCursor = (u8 *)stepCursor + (*(s16 *)(self + 0x22)) * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)stepCursor * 4));
}
