s32 sub_0808DBF8(s32, s32, s32);
s32 sub_080C31E0(void *, s32);

/* Spawn two kind-1 effects either side of the work area's recorded position:
 * one at x - 4.0 and one at x + 4.0, both at y + 5.0 (16.16 fixed point), each
 * with parameter 8; then call the entity's script callback. */
void sub_0804E9B0(void *arg0) {
    void *work;

    work = *(void **)((s8 *)arg0 + 0x3C);
    sub_0808DBF8(*(s32 *)((s8 *)work + 8) + 0xFFFC0000, *(s32 *)((s8 *)work + 0xC) + 0x50000, 8);
    sub_0808DBF8(*(s32 *)((s8 *)work + 8) + 0x40000, *(s32 *)((s8 *)work + 0xC) + 0x50000, 8);
    sub_080C31E0(arg0, *(s32 *)((s8 *)arg0 + 0x24));
}
