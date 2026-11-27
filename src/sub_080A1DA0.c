void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);
void advanceMotion(void *, s32);

/* Script command: flag the work object's display state active and step its
 * physics; after the step has run 4 times, clear the counter and advance. */
void sub_080A1DA0(void *arg0) {
    u8 *self = arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *stepCmd;
    s32 stepOffset;
    s32 *scriptTable;
    *(u8 *)(*(u8 **)(work + 0x28) + 1) = 1;
    advanceMotion(work, 0);
    stepOffset = *(s16 *)(self + 0x22) * 2;
    stepCmd = (u8 *)(stepOffset + (u32)self);
    if (*(u8 *)(stepCmd + 0x19) == 4) {
        *(u8 *)(stepCmd + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
}
