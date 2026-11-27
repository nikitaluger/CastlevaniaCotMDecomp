extern void sub_080C31E8(void *, void *, s32, s32);

/* Script step handler: when the current slot's command byte is 0x28, clear the
 * slot's flag byte and dispatch the next script command through the command
 * table at gMenuScriptCallback. */
void sub_080B1704(void *arg0) {
    u8 *self = (u8 *)arg0;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x28) {
        s32 *lit;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        lit = (s32 *)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 2, *lit);
    }
}
