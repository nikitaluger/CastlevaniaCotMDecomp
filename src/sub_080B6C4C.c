void stepAnimationTrack(s32, void *);
void setAnimationFrame(s32, void *, s32, s32);
void sub_08011EE8(void *, s32, s32);
void sub_080B72CC(void *);
void sub_08005E80(s32);
void sub_080C31E4(void *, void *, s32);

/* Projectile update: integrate its motion and, when it touches the ground or
 * any collision flag is set, stop it, play its burst animation and sound
 * 0x18D, then run the next script command. */
void sub_080B6C4C(void *arg0) {
    s32 anim = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *motion = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *animDesc = motion + 0x34;

    stepAnimationTrack(anim, animDesc);
    sub_08011EE8(motion, 0, 0);
    if ((1 & *(u16 *)(*(u8 **)(motion + 0x28) + 0x14)) || (*(u16 *)(motion + 2) != 0)) {
        void **litp;
        sub_080B72CC(arg0);
        *(u32 *)(motion + 0x10) = 0;
        *(u32 *)(motion + 0x14) = 0;
        setAnimationFrame(anim, animDesc, 0x1F, 0);
        sub_08005E80(0x18D);
        ((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2)[0x19] = 0;
        litp = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*litp);
    }
}
