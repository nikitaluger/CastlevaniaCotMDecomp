extern void sub_080C31E4(void *, void *, s32);

/*
 * Command script step: when the work state's +0x18 completion flag (bit 1) is
 * set, clears the sub-object's flag byte at +1, resets the script counter and
 * advances the command script.
 */
void sub_08096CDC(void *entity) {
    u8 *state = *(u8 **)((u8 *)entity + 0x3C);
    if (*(u8 *)(state + 0x18) & 2) {
        void **scriptTable;
        *(u8 *)(*(u8 **)(state + 4) + 1) = 0;
        *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
        scriptTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, (s32)*scriptTable);
    }
}
