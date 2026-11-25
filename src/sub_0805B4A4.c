extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);

/* Script entry (mode 2): set the entity's mode bytes, clear the current script
 * slot's counter, run the script-advance callback, then dispatch the handler
 * selected by the current script byte. */
void sub_0805B4A4(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *mode = self + 0x40;
    s32 zero = 0;
    u8 *script;
    s32 *lit;

    *mode = 2;
    *(mode - 4) = 1;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
    lit = (s32 *)0x08671BB0;
    script = self + 0x18;
    sub_080C31E4(script, self + 0x22, *lit);
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    script += *(s16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)script * 4));
}
