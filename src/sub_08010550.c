extern void sub_08001480(void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Script command: spawn a type-3 child actor attached to self, clear the current
 * step's progress byte (+0x19 + step*2), let the step runner advance the step
 * index at +0x22, mark the new step's progress byte as 1 and dispatch the new
 * step's command handler from the table at +0x14. */
void sub_08010550(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *steps;
    s32 *stepFnTable;
    sub_08001480(self, 0x03);
    *(u8 *)((s16)*(u16 *)(self + 0x22) * 2 + self + 0x19) = 0;
    stepFnTable = (s32 *)0x08671BB0;
    steps = self + 0x18;
    sub_080C31E4(steps, self + 0x22, *stepFnTable);
    *(u8 *)((s16)*(u16 *)(self + 0x22) * 2 + self + 0x19) += 1;
    steps += (s16)*(u16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)steps * 4));
}
