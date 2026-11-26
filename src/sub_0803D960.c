extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Play sprite animation 9 on the entity; if the work velocity at +0x14 is
 * non-negative, clear the current script step byte and advance the command. */
void sub_0803D960(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    setAnimationFrame(sprite, work + 0x34, 9, 0);
    if (*(s32 *)(work + 0x14) >= 0) {
        s16 step = *(s16 *)(self + 0x22);
        s32 *scriptTable;
        *(u8 *)(self + step * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
}
