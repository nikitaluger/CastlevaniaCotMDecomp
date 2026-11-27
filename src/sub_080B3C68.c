extern void sub_080C31E8(void *, void *, s32, s32);

/* Script step handler: when the current slot's command byte is 4, clear it and
 * dispatch the slot's command through the table at gScriptStepCallbacks. */
void sub_080B3C68(void *arg0) {
    u8 *self = (u8 *)arg0;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 4) {
        s32 *lit;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *lit);
    }
}
