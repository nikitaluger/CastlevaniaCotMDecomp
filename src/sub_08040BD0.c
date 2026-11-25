void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Script command: clear the actor's flag at +0x74 and the current step's
 * progress byte, let the step runner advance the step index, mark the new step
 * as started and dispatch its command handler from the table at +0x14. */
void sub_08040BD0(void *self) {
    u8 *steps;
    const u32 *stepFnTable;
    *(u8 *)((u8 *)self + 0x74) = 0;
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    stepFnTable = (const u32 *)0x08671BB0;
    steps = (u8 *)self + 0x18;
    sub_080C31E4(steps, (u8 *)self + 0x22, *stepFnTable);
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    steps += (s32)*(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u8 *)steps * 4 + *(u32 *)((u8 *)self + 0x14)));
}
