extern void createChildObject(void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, void *, void *);

/* Script command: reset the progress byte at +0x17 + step*2, then run the
 * script-step routine at gMenuScriptCallback with the step array, the step index and the
 * script state pointer held at gMenuState. */
void sub_080106E8(void *arg0) {
    u8 *self = (u8*)arg0;
    void *runner;
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x17) = 0;
    runner = *(void**)0x08671BD8;
    sub_080C31E8(self + 0x18, self + 0x22, *(void**)0x020278D0, runner);
}

/* Script command: spawn a type-0x17 child actor attached to self, clear the
 * current step's progress byte (+0x19 + step*2), let the step runner advance the
 * step index at +0x22, mark the new step's progress byte as 1 and dispatch the
 * new step's command handler from the table at +0x14. */
void sub_08010760(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *steps;
    s32 *stepFnTable;
    createChildObject(self, 0x17);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) = 0;
    stepFnTable = (s32*)0x08671BB0;
    steps = self + 0x18;
    sub_080C31E4(steps, self + 0x22, *stepFnTable);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) += 1;
    steps += (s16)*(u16*)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32*)(*(u32*)(self + 0x14) + *(u8*)steps * 4));
}

/* Script command: spawn a type-0x1E child actor attached to self, clear the
 * current step's progress byte (+0x19 + step*2), let the step runner advance the
 * step index at +0x22, mark the new step's progress byte as 1 and dispatch the
 * new step's command handler from the table at +0x14. */
void sub_080105F0(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *steps;
    s32 *stepFnTable;
    createChildObject(self, 0x1E);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) = 0;
    stepFnTable = (s32*)0x08671BB0;
    steps = self + 0x18;
    sub_080C31E4(steps, self + 0x22, *stepFnTable);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) += 1;
    steps += (s16)*(u16*)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32*)(*(u32*)(self + 0x14) + *(u8*)steps * 4));
}

/* Script command: spawn a type-0x1D child actor attached to self, clear the
 * current step's progress byte (+0x19 + step*2), let the step runner advance the
 * step index at +0x22, mark the new step's progress byte as 1 and dispatch the
 * new step's command handler from the table at +0x14. */
void sub_08010834(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *steps;
    s32 *stepFnTable;
    createChildObject(self, 0x1D);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) = 0;
    stepFnTable = (s32*)0x08671BB0;
    steps = self + 0x18;
    sub_080C31E4(steps, self + 0x22, *stepFnTable);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) += 1;
    steps += (s16)*(u16*)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32*)(*(u32*)(self + 0x14) + *(u8*)steps * 4));
}
