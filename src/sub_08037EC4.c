extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Script command: clear the actor's flag at +0x4C and the current step's
 * progress byte, let the step runner advance the step index, mark the new step
 * as started and dispatch its command handler from the table at +0x14. */
void sub_08037EC4(void *arg0) {
    void *steps;
    const u32 *stepFnTable;
    *(u8 *)(arg0 + 0x4C) = 0;
    *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
    stepFnTable = (const u32 *)0x08671BB0;
    steps = arg0 + 0x18;
    sub_080C31E4(steps, arg0 + 0x22, *stepFnTable);
    *(u8 *)(arg0 + (s32)*(s16 *)(arg0 + 0x22) * 2 + 0x19) += 1;
    steps += (s32)*(s16 *)(arg0 + 0x22) * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)((u8 *)arg0 + 0x14) + *(u8 *)steps * 4));
}
