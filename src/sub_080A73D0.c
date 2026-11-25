extern void sub_080C31E4(void *, void *, s32);

/* End the current script step once its command byte reaches 8: clear the
 * command and hand control back to the script dispatcher. */
void sub_080A73D0(void *arg0) {
    u8 *self = (u8 *)arg0;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 8) {
        s32 *scriptTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
}
