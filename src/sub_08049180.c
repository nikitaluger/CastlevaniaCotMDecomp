extern void stepAnimationTrack(s32, void *);

/* Recoils a homing entity vertically whenever the animation-driven contact
 * code carried on the sprite changes, then caches the new code in the steer
 * block. Returns 1 only for a code-0 contact. */
s32 sub_08049180(s32 sprite, void *animState, void *motion, void *steer) {
    s32 impulse = 0;
    s32 rebounded = impulse;
    stepAnimationTrack(sprite, animState);
    if (*(u16 *)((u8 *)steer + 2) != *(u16 *)((u8 *)sprite + 0x28)) {
        u8 contactType = *(u8 *)((u8 *)steer + 1);
        switch (contactType) {
        case 0: impulse = 0xFFFE0000; break;
        case 5: impulse = 0xFFFF0000; break;
        }
        switch (*(u16 *)((u8 *)sprite + 0x28)) {
        case 0:
            *(s32 *)((u8 *)motion + 0xC) -= impulse;
            rebounded = 1;
            break;
        case 3:
            *(s32 *)((u8 *)motion + 0xC) += impulse;
            break;
        case 6:
            *(s32 *)((u8 *)motion + 0xC) += impulse;
            break;
        case 7:
            *(s32 *)((u8 *)motion + 0xC) -= impulse;
            break;
        }
        *(u16 *)((u8 *)steer + 2) = *(u16 *)((u8 *)sprite + 0x28);
    }
    return rebounded;
}
