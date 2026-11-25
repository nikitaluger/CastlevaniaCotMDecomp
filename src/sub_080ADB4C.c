extern void sub_080C31E4(void *, void *, s32);

/* When the current script step's counter reaches 0x1E, reset it to zero and
 * advance the script to its next command. */
void sub_080ADB4C(void *arg0) {
    u8 *self = (u8 *)arg0;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x1E) {
        s32 *scriptTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
}
