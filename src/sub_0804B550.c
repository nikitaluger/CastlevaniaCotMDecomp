s32 setAnimationFrame(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);
s32 sub_080C364C(s32, s32);
s32 sub_080C31E0(s32, s32);
s32 sub_0800583C(s32);

/* Play sprite animation 5 on the entity; if the animator's finish flag (bit 1
 * of its state byte) is set, clear the current script step byte and advance
 * the entity's command script. */
void sub_0804B550(void *arg0) {
    s32 sprite = *(s32 *)((u8 *)arg0 + 0x38);
    void *animState = (u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x34;
    setAnimationFrame(sprite, animState, 5, 0);
    if (*(u8 *)animState & 2) {
        s32 step = *(s16 *)((u8 *)arg0 + 0x22);
        s32 *scriptTable;
        *(u8 *)((u8 *)arg0 + step * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptTable);
    }
}
