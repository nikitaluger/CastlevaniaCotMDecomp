extern void sub_080C31E4(void *, void *, s32);

struct Work10C {
    u8 pad[0x10C];
    u32 value;
};

/* On script step 0x78, set the work parameter at +0x10C to 0xC000, clear the
 * step byte and advance to the next script command. */
void sub_080A6A6C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x78) {
        s32 *stepTable;
        ((struct Work10C *)work)->value = (0xC0 << 8);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        stepTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *stepTable);
    }
}
