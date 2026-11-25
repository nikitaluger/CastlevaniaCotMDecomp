extern void sub_080C31E4(void *a, void *b, s32 c);

/*
 * Command script step: when the work state's +0xE value reaches 1, latch it
 * into +0xC, reset the script counter and advance the command script.
 */
void sub_080922A4(void *entity) {
    u8 *state = *(u8 **)((u8 *)entity + 0x3C);
    s32 index = 0xE;
    s32 value = *(s16 *)(state + index);
    if (value == 1) {
        void **scriptTable;
        u8 zero = 0;
        *(s16 *)(state + 0xC) = value;
        *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = zero;
        scriptTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, (s32)*scriptTable);
    }
}
