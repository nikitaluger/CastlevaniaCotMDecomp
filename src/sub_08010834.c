extern void sub_08001480(void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, void *, void *);

/* Clears the byte at self+0x17 for the current script step, then dispatches
 * that step through sub_080C31E8 with the two global tables. */
void sub_080106E8(void *arg0) {
    u8 *self = (u8*)arg0;
    void *altTable;
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x17) = 0;
    altTable = *(void**)0x08671BD8;
    sub_080C31E8(self + 0x18, self + 0x22, *(void**)0x020278D0, altTable);
}

/* Spawns a kind-0x17 child parented to self, resets the current script-step
 * counter, runs the step, then calls the step's command callback. */
void sub_08010760(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *scriptData;
    s32 *scriptTable;
    sub_08001480(self, 0x17);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) = 0;
    scriptTable = (s32*)0x08671BB0;
    scriptData = self + 0x18;
    sub_080C31E4(scriptData, self + 0x22, *scriptTable);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) += 1;
    scriptData += (s16)*(u16*)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32*)(*(u32*)(self + 0x14) + *(u8*)scriptData * 4));
}

/* Spawns a kind-0x1E child parented to self, resets the current script-step
 * counter, runs the step, then calls the step's command callback. */
void sub_080105F0(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *scriptData;
    s32 *scriptTable;
    sub_08001480(self, 0x1E);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) = 0;
    scriptTable = (s32*)0x08671BB0;
    scriptData = self + 0x18;
    sub_080C31E4(scriptData, self + 0x22, *scriptTable);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) += 1;
    scriptData += (s16)*(u16*)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32*)(*(u32*)(self + 0x14) + *(u8*)scriptData * 4));
}

/* Spawns a kind-0x1D child parented to self, resets the current script-step
 * counter, runs the step, then calls the step's command callback. */
void sub_08010834(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *scriptData;
    s32 *scriptTable;
    sub_08001480(self, 0x1D);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) = 0;
    scriptTable = (s32*)0x08671BB0;
    scriptData = self + 0x18;
    sub_080C31E4(scriptData, self + 0x22, *scriptTable);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) += 1;
    scriptData += (s16)*(u16*)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32*)(*(u32*)(self + 0x14) + *(u8*)scriptData * 4));
}
