/* Starts the animation described by the u16 pair at arg2 on the state at arg1,
 * storing the second word on the calling actor at +0x28. */
void sub_08010D50(void *arg0, void *arg1, void *arg2, u8 arg3) {
    u8 *animState = (u8 *)arg1;
    u16 *frameData = (u16 *)arg2;
    u8 index = arg3;
    u16 frameId = frameData[0];
    *(u16 *)(animState + 2) = frameId;
    *(u32 *)(animState + 4) = 0;
    animState[1] = 1;
    animState[0] = index;
    *(u16 *)((u8 *)arg0 + 0x28) = frameData[1];
    if ((frameId << 16) == 0) {
        u8 zero = 0;
        animState[1] = zero;
        animState[0] = index | 2;
    }
}

extern void sub_080C31E8(void *, void *, s32, s32);

/* Clears the byte at self+0x17 for the current script step, then dispatches
 * the step through sub_080C31E8 with the global table. */
void sub_08010B04(void *arg0) {
    u8 *self = (u8 *)arg0;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
    sub_080C31E8(self + 0x18, self + 0x22, 0, *(s32 *)0x08671BD8);
}

extern void sub_08001480(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Spawns a kind-0x21 child parented to self, resets the current script-step
 * counter, runs the step, then calls the step's command callback. */
void sub_080109F8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *scriptData;
    s32 *scriptTable;
    sub_08001480(self, 0x21);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    scriptTable = (s32 *)0x08671BB0;
    scriptData = self + 0x18;
    sub_080C31E4(scriptData, self + 0x22, *scriptTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    scriptData = scriptData + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)scriptData * 4));
}

/* Clears the byte at self+0x17 for the current step and dispatches it with
 * argument 7 or 8 depending on the global state at 0x02025FF0+0x0C. */
void sub_08010954(void *arg0) {
    u8 *self = (u8 *)arg0;
    if (*(s32 *)((u8 *)0x02025FF0 + 0x0C) == 2) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        sub_080C31E8(self + 0x18, self + 0x22, 7, *(s32 *)0x08671BD8);
    } else {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        sub_080C31E8(self + 0x18, self + 0x22, 8, *(s32 *)0x08671BD8);
    }
}
