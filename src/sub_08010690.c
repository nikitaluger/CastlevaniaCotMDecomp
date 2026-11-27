extern void createChildObject(void *, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Spawns a kind-0x15 child parented to self, resets the current script-step
 * counter, runs the step, then calls the step's command callback. */
void sub_08010690(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *scriptData;
    s32 *scriptTable;
    createChildObject(self, 0x15);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) = 0;
    scriptTable = (s32*)0x08671BB0;
    scriptData = self + 0x18;
    sub_080C31E4(scriptData, self + 0x22, *scriptTable);
    *(u8*)((s16)*(u16*)(self + 0x22) * 2 + self + 0x19) += 1;
    scriptData += (s16)*(u16*)(self + 0x22) * 2;
    sub_080C31E0(self, *(u32*)(*(u32*)(self + 0x14) + *(u8*)scriptData * 4));
}
