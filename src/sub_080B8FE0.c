extern void sub_08005E80(s32);
extern void sub_08014620(s32, s32, s32);
extern void sub_0808DBF8(s32, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Spawn one effect slightly above the entity's position and another at its feet,
 * play sound 0x83, then switch the entity to its next script state. */
void sub_080B8FE0(void *entity) {
    void *work;

    work = *(void **)((u8 *)entity + 0x3C);
    sub_0808DBF8(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC) + 0xA0000, 8);
    sub_08014620(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC), 8);
    sub_08005E80(0x83);
    sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
}
