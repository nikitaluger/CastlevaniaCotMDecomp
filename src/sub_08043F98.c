extern s32 sub_0808DC40(s32, s32, s32);
extern s32 sub_080C31E0(void *, s32);

/* Spawn a variant-2 effect at the sub-object's fixed-point position (+8, +0xC)
 * with parameter 8, then advance the script. */
void sub_08043F98(void *arg0) {
    void *sub;

    sub = *(void **)((s8 *)arg0 + 0x3C);
    sub_0808DC40(*(s32 *)((s8 *)sub + 8), *(s32 *)((s8 *)sub + 0xC), 8);
    sub_080C31E0(arg0, *(s32 *)((s8 *)arg0 + 0x24));
}
