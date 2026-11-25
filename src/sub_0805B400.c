extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);

/* Script entry (mode 1): set the entity's mode bytes, clear the current script
 * slot's counter, run the script-advance callback, then dispatch the handler
 * selected by the current script byte. */
void sub_0805B400(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *mode = self + 0x40;
    s32 zero = 0;
    u8 *stepBase;
    s32 *advanceTable;

    *mode = 1;
    *(mode - 4) = 1;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    advanceTable = (s32 *)0x08671BB0;
    stepBase = self + 0x18;
    sub_080C31E4(stepBase, self + 0x22, *advanceTable);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    stepBase += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)stepBase * 4));
}
