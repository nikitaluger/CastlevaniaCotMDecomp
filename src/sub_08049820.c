extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Script step transition: sets the mode flag from the linked state word
 * (0xFF when it is empty, 1 otherwise), clears the mode byte and the step
 * counter, advances the script and runs the handler for the new step. */
void sub_08049820(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *stepPtr;
    s32 *scriptHandlers;

    if (*(u16 *)(*(u32 *)(*(u32 *)(self + 0xAC) + 0x04) + 0x06) == 0) {
        *(u8 *)(self + 0x70) = 0xFF;
    } else {
        *(u8 *)(self + 0x70) = 0x01;
    }
    *(u8 *)(self + 0x6C) = 0;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    scriptHandlers = (s32 *)0x08671BB0;
    stepPtr = self + 0x18;
    sub_080C31E4(stepPtr, self + 0x22, *scriptHandlers);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepPtr = stepPtr + *(s16 *)(self + 0x22) * 2;
    {
        u8 handlerId = *stepPtr;
        void *handlerTable = *(void **)(self + 0x14);
        sub_080C31E0(self, *(void **)((u8 *)handlerTable + handlerId * 4));
    }
}
