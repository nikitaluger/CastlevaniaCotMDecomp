extern void sub_08011368(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08001480(void *, s32);
extern void sub_080113A8(void *, void *);
extern void sub_080415D4(s32, s32, void *, void *);

/* Restart the actor: play animation 9, install command table 0x0866DA6C, push
 * one script step (+0x22), dispatch that step's handler once, then pop the step
 * again. */
void sub_08029A7C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u32 stepOffset;
    u8 *steps;
    sub_08011368(*(void **)(self + 0x38), *(void **)(self + 0x3C) + 0x34, 9, 1);
    *(u32 *)(self + 0x14) = 0x0866DA6C;
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) + 1);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepOffset = (s32)*(s16 *)(self + 0x22) * 2;
    steps = self + 0x18;
    sub_080C31E0(self, *(void **)(*(u8 *)(steps + stepOffset) * 4 + *(u32 *)(self + 0x14)));
    *(u16 *)(self + 0x22) = (u16)(*(u16 *)(self + 0x22) - 1);
}

/* Script command: set the flag byte at +0x74, clear the current step's progress
 * byte, let the step runner advance the step index, mark the new step as started
 * and dispatch its command handler. */
void sub_08040C70(void *arg0) {
    void *flag = arg0 + 0x74;
    u8 zero = 0;
    void *steps;
    const u32 *stepFnTable;
    *(u8 *)flag = 1;
    *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) = zero;
    stepFnTable = (const u32 *)0x08671BB0;
    steps = arg0 + 0x18;
    sub_080C31E4(steps, arg0 + 0x22, *stepFnTable);
    *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) += 1;
    steps += (s32)*(s16 *)(arg0 + 0x22) * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)((u8 *)arg0 + 0x14) + *(u8 *)steps * 4));
}

/* Animation step: advance the sprite animator and, when it signals a finished
 * frame (bit 2 set), run the frame-complete handler and advance the script step. */
void sub_080412F8(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    s32 *stepFnTable;
    sub_080113A8((void *)sprite, (void *)anim);
    if (*(u8 *)anim & 2) {
        sub_080415D4(0, sprite, (void *)work, (void *)anim);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        stepFnTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *stepFnTable);
    }
}

/* Script command: spawn a type-6 child actor attached to self, clear the current
 * step's progress byte (+0x19 + step*2), let the step runner advance the step
 * index at +0x22, mark the new step's progress byte as 1 and dispatch the new
 * step's command handler from the table at +0x14. */
void sub_080108FC(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *steps;
    s32 *stepFnTable;
    sub_08001480(self, 0x06);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) = 0;
    stepFnTable = (s32*)0x08671BB0;
    steps = self + 0x18;
    sub_080C31E4(steps, self + 0x22, *stepFnTable);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) += 1;
    steps += (s16)*(u16*)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32*)(*(u32*)(self + 0x14) + *(u8*)steps * 4));
}
