extern s32 sub_08005820(s32);
extern void sub_08011368(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Play sprite animation 0xB on the entity; if work+2 flag bit 2 is set, clear
 * the current script step byte and advance the entity's command script. */
void sub_0803D9A0(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    sub_08011368(sprite, work + 0x34, 0x0B, 0);
    if (*(u16 *)(work + 0x02) & 4) {
        s16 step = *(s16 *)(self + 0x22);
        s32 *scriptTable;
        *(u8 *)(self + step * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
}
