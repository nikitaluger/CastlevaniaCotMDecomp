extern void sub_08011368(void *, void *, s32, s32);
extern void sub_0801165C(void *, s32);
extern void sub_08044FD4(s32, void *, void *, void *);

/* Launch the projectile (spawn id 0x2D82) and run its upward hit test; once the
 * projectile has travelled past 0x8000 units, switch it to animation 0x17. */
void sub_08044BD0(void *arg0) {
    u8 *projectile;
    u8 *animator;
    u8 *hitState;
    s32 owner;
    owner = *(s32 *)((u8 *)arg0 + 0x38);
    projectile = *(u8 **)((u8 *)arg0 + 0x3C);
    animator = projectile + 0x34;
    hitState = (u8 *)((u32)projectile + 0x48);
    sub_0801165C(projectile, 0x2D82);
    if (*(s32 *)(projectile + 0x14) > (s32)(0x80 << 8)) {
        sub_08011368((void *)owner, animator, 0x17, 0);
    }
    sub_08044FD4(1, arg0, projectile, hitState);
}
