void sub_080C31E4(void *, void *, s32);
s32 sub_08005F1C(s32);

/* Script step: when the step byte at the current script index passes 0x1D and
 * both flag checks come back clear, reset that byte to 0 and advance the script. */
void sub_08008B00(void *arg0) {
    u8 *script = (u8 *)arg0;
    if (*(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) > 0x1D) {
        if (sub_08005F1C(0xC1 << 1) == 0) {
            s32 flagCheck = sub_08005F1C(0x73);
            if (flagCheck == 0) {
                s32 *advanceFunc;
                *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) = flagCheck;
                advanceFunc = (s32 *)0x08671BB0;
                sub_080C31E4(script + 0x18, script + 0x22, *advanceFunc);
            }
        }
    }
}
