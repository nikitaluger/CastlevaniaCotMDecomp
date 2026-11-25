void sub_08011368(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Script step: play sprite animation 0xC; when the animator's finish flag
 * (bit 1 of its state byte) is set, clear this step's script byte and advance
 * the entity's command script. */
void sub_0804CA74(void *self) {
    void *sprite = *(void **)((u8 *)self + 0x38);
    u8 *work = *(u8 **)((u8 *)self + 0x3C);
    u8 *animState = work + 0x34;
    u32 *scriptTable;
    sub_08011368(sprite, animState, 0xC, 0);
    if (2 & *animState) {
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self) + 0x19) = 0;
        scriptTable = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *scriptTable);
    }
}
