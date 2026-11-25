extern void sub_080C31E4(void *, void *, s32);

/* Script-step callback: write 0xBF and 0x10 into the shared state word at
 * 0x03000830, clear the current command byte, then dispatch the follow-up
 * script from the default command table. */
void sub_08001850(void *arg0) {
    u8 *self = (u8 *)arg0;
    u16 *reg = (u16 *)0x03000830;
    u8 z = 0;
    s32 *lit;
    reg[2] = 0xBF;
    reg[4] = 0x10;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = z;
    lit = (s32 *)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *lit);
}
