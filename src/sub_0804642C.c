extern s32 sub_0800583C(s32);
extern void sub_0801165C(void *, s32);
extern void sub_0808DC40(s32, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Launch the projectile (spawn id 0x2D82). While the script's repeat counter is
 * below 3, spawn a short-lived effect at a randomised x offset; once the
 * projectile is moving upward, hand control to the stored script handler. */
void sub_0804642C(void *arg0) {
    void *projectile;

    projectile = *((void **)((s8 *)arg0 + 0x3C));
    sub_0801165C(projectile, 0x2D82);
    if (!(3 & *((u8 *)(((*((s16 *)((s8 *)arg0 + 0x22)) * 2) + (s8 *)arg0) + 0x19)))) {
        sub_0808DC40(*((s32 *)((s8 *)projectile + 8)) + sub_0800583C(0x80000), *((s32 *)((s8 *)projectile + 0xC)), 8);
    }
    if (*((s32 *)((s8 *)projectile + 0x14)) > 0) {
        sub_080C31E0(arg0, *((s32 *)((s8 *)arg0 + 0x24)));
    }
}
