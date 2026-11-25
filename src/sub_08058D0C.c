extern void sub_0808DBF8(s32, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Once the current script step has run for more than 0x22 frames, spawn an
 * impact effect just above the entity and switch to its next state handler. */
void sub_08058D0C(void *entity) {
    void *work;

    work = *(void **)((u8 *)entity + 0x3C);
    if ((u32) *((u8 *)((*(s16 *)((u8 *)entity + 0x22) * 2) + (u8 *)entity) + 0x19) > 0x22U) {
        sub_0808DBF8(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC) + 0x80000, 8);
        sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
    }
}
