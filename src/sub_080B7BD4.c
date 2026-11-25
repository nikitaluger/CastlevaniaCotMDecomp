void sub_080B9818(void *obj, s32 value);
void sub_080C31E4(void *base, void *index, s32 table);

/* Script-step handler for a travelling object: once the current trail slot's
 * counter reaches 0x10, restart the mover with its stored step value, clear the
 * slot and dispatch the next command from the script table. */
void sub_080B7BD4(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *mover = *(u8 **)(self + 0x3C);
    s32 *lit;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x10) {
        sub_080B9818(*(s32 *)(mover + 0x48), *(s32 *)(mover + 8));
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
