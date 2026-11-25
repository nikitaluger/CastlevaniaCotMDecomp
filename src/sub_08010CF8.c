/* Start a frame from an animation table: store the frame's duration at
 * anim+2, reset the timer at anim+4, set step to 1 and the flag byte to the
 * given flags, publish the frame code to sprite+0x28; a zero duration ends the
 * animation immediately (step 0, done bit set). */
void sub_08010D50(void *arg0, void *arg1, void *arg2, u8 arg3) {
    u8 *anim = (u8 *)arg1;
    u16 *frame = (u16 *)arg2;
    u8 flags = arg3;
    u16 duration = frame[0];
    *(u16 *)(anim + 2) = duration;
    *(u32 *)(anim + 4) = 0;
    anim[1] = 1;
    anim[0] = flags;
    *(u16 *)((u8 *)arg0 + 0x28) = frame[1];
    if ((duration << 16) == 0) {
        u8 zero = 0;
        anim[1] = zero;
        anim[0] = flags | 2;
    }
}

extern void sub_08001480(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Script command: spawn a type-0x23 child actor attached to self, clear the
 * current step's progress byte (+0x19 + step*2), let the step runner advance the
 * step index at +0x22, mark the new step's progress byte as 1 and dispatch the
 * new step's command handler from the table at +0x14. */
void sub_08010CF8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *steps;
    s32 *stepFnTable;
    sub_08001480(self, 0x23);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    stepFnTable = (s32 *)0x08671BB0;
    steps = self + 0x18;
    sub_080C31E4(steps, self + 0x22, *stepFnTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    steps = steps + *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)steps * 4));
}

/* Wait for the actor's children (list head at +0x30) to finish: once none are
 * left, clear the current step's progress byte, advance the step index and
 * dispatch the next step's command handler. */
void sub_08010C58(void *arg0) {
    u8 *self = (u8 *)arg0;
    if (*(s32 *)(self + 0x30) == 0) {
        u8 *steps;
        s32 *stepFnTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        stepFnTable = (s32 *)0x08671BB0;
        steps = self + 0x18;
        sub_080C31E4(steps, self + 0x22, *stepFnTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        steps = steps + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)steps * 4));
    }
}

/* Wait for the actor's children (list head at +0x30) to finish: once none are
 * left, clear the progress byte at +0x17 + step*2 and run the step routine at
 * D_08671BB4 with the step array and step index. */
void sub_08010C2C(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 childCount = *(s32 *)(self + 0x30);
    if (childCount == 0) {
        s32 *stepFnTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = (u8)childCount;
        stepFnTable = (s32 *)0x08671BB4;
        sub_080C31E4(self + 0x18, self + 0x22, *stepFnTable);
    }
}
