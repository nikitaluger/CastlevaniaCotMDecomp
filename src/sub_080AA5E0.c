extern s32 sub_08005E80(s32);
extern s32 sub_0808DBF8(s32, s32, s32);
extern s32 sub_080C31E0(void *, s32);

/* Entity action: play sound 0x18A, spawn a kind-1 effect at the work area's
 * recorded fixed-point (x, y), then chain to the entity's saved script
 * callback through the indirect-call thunk. */
void sub_080AA5E0(void *entity) {
    void *work;

    work = *(void **)((s8 *)entity + 0x3C);
    sub_08005E80(0x18A);
    sub_0808DBF8(*(s32 *)((s8 *)work + 8), *(s32 *)((s8 *)work + 0xC), 8);
    sub_080C31E0(entity, *(s32 *)((s8 *)entity + 0x24));
}
