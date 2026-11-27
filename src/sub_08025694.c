s32 setAnimationFrame(s32, s32, s32, s32);
s32 spawnJitteredParticles(s32, s32, s32, s32, s32, s32);
s32 sub_080C31E0(void *, s32);
u8 sub_080C389C(u8, s32);

/* Update this spawner entity: set animation frame 9, spawn a particle just
 * below it every sixth frame, then run its script update while its active
 * flag is set. */
void sub_08025694(void *arg0) {
    s32 animOwner;
    s8 *subObj;
    animOwner = *(s32 *)((s8 *)arg0 + 0x38);
    subObj = *(s8 **)((s8 *)arg0 + 0x3C);
    setAnimationFrame(animOwner, (s32)(subObj + 0x34), 9, 0);
    if (sub_080C389C(*(u8 *)((s8 *)arg0 + (*(s16 *)((s8 *)arg0 + 0x22) * 2) + 0x19), 6) == 1) {
        spawnJitteredParticles(1, 1, *(s32 *)((s8 *)subObj + 8), *(s32 *)((s8 *)subObj + 0xC) + 0xC0000, 0x40000, 0x40000);
    }
    if (2 & *(u8 *)((s8 *)subObj + 0x34)) {
        sub_080C31E0(arg0, *(s32 *)((s8 *)arg0 + 0x24));
    }
}
