extern void sub_08011368(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Refresh animation 0xB on the motion state's animator, then clamp the state's
 * value (+0xC) to the limit state's value (+0x48->+0xC), zeroing its +0x14
 * speed/limit word when clamped. If the animator's byte bit 1 is set and the
 * clamp applied, clear this actor's script-action byte and advance the script. */
void sub_0801B784(void *obj) {
    u8 *actor = (u8 *)obj;
    s32 sprite = *(s32 *)(actor + 0x38);
    u8 *motion = *(u8 **)(actor + 0x3C);
    u8 *animState = motion + 0x34;
    u8 *limitState = motion + 0x48;
    s32 *advance;
    sub_08011368(sprite, animState, 0xB, 0);
    *(u32 *)(motion + 0x14) = 0x6000;
    if (*(s32 *)(motion + 0xC) >= *(s32 *)(limitState + 0xC)) {
        *(s32 *)(motion + 0xC) = *(s32 *)(limitState + 0xC);
        *(u32 *)(motion + 0x14) = 0;
    }
    if (*(u8 *)animState & 2) {
        if (*(s32 *)(motion + 0xC) >= *(s32 *)(limitState + 0xC)) {
            *(s32 *)(motion + 0xC) = *(s32 *)(limitState + 0xC);
            *(u32 *)(motion + 0x14) = 0;
            *(u8 *)(actor + *(s16 *)(actor + 0x22) * 2 + 0x17) = 0;
            advance = (s32 *)0x08671BD8;
            sub_080C31E8(actor + 0x18, actor + 0x22, 1, *advance);
        }
    }
}
