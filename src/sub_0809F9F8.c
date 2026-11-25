extern void sub_0800168C(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);

/* Spawn the entity's work object, program its initial animation frame and
 * coordinates, then clear the current script step, advance the script and
 * dispatch the handler selected by the new command byte. */
void sub_0809F9F8(u8 *self) {
    u8 *work;
    s32 zero;
    s16 stepIndex;
    u8 *stepPtr;
    u32 scriptCbAddr;

    sub_0800168C(self, 0, 0x48, 0);

    work = *(u8 **)(self + 0x3C);
    if (work == 0) {
        sub_080C31E0(self, *(void **)(self + 0x24));
        return;
    }

    zero = 0;
    *(u16 *)(work + 0x1C) = 0x4C;
    *(u32 *)(work + 0x08) = *(u32 *)(self + 0x5C);
    *(u32 *)(work + 0x0C) = *(u32 *)(self + 0x6C);
    *(u16 *)(self + 0x02) |= 0x1000;

    stepIndex = *(s16 *)(self + 0x22);
    self[stepIndex * 2 + 0x19] = (u8)zero;

    scriptCbAddr = (u32)0x08671BB0;
    stepPtr = self + 0x18;
    sub_080C31E4(stepPtr, self + 0x22, *(u32 *)scriptCbAddr);

    stepIndex = *(s16 *)(self + 0x22);
    self[stepIndex * 2 + 0x19]++;

    stepIndex = *(s16 *)(self + 0x22);
    stepPtr = stepPtr + stepIndex * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + stepPtr[0] * 4));
}
