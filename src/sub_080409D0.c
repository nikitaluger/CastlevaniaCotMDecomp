extern void sub_08005E80(s32);
extern s32 sub_0808DBF8(s32, s32, s32);
extern s32 sub_080C31E0(void *, s32);

/* Play sound 0x18A, spawn a kind-1 effect 8.0 units above the work area's
 * recorded position (16.16 fixed point) with parameter 8, then chain to the
 * entity's script callback. */
void sub_080409D0(void *arg0) {
    void *work;

    work = *(void **)((s8 *)arg0 + 0x3C);
    sub_08005E80(0x18A);
    sub_0808DBF8(*(s32 *)((s8 *)work + 8), *(s32 *)((s8 *)work + 0xC) + 0x80000, 8);
    sub_080C31E0(arg0, *(s32 *)((s8 *)arg0 + 0x24));
}
