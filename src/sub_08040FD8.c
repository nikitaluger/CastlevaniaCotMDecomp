extern s32 sub_080415D4(s32, s32, void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Set up this entity's first pose, reset its motion/state data, bump the state
 * counter and dispatch the handler selected from the table at 0x08671BB0. */
void sub_08040FD8(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *work;
    u8 *statePtr;
    s32 sprite;
    s32 *handlerTable;

    sprite = *((s32 *)(self + 0x38));
    work = *((u8 **)(self + 0x3C));
    statePtr = work;

    sub_080415D4(0, sprite, statePtr, (s32)(statePtr + 0x34));
    *((s32 *)(statePtr + 0x10)) = 0;
    *((s32 *)(statePtr + 0x14)) = 0;
    *((u8 *)((self + ((*((s16 *)(self + 0x22))) * 2)) + 0x19)) = 0;

    handlerTable = (s32 *)0x08671BB0;
    statePtr = self + 0x18;
    sub_080C31E4(statePtr, self + 0x22, *handlerTable);
    *((u8 *)((self + ((*((s16 *)(self + 0x22))) * 2)) + 0x19)) += 1;
    statePtr = statePtr + ((*((s16 *)(self + 0x22))) * 2);
    sub_080C31E0(self, *((void **)((*((u32 *)(self + 0x14))) + ((*((u8 *)statePtr)) * 4))));
}
