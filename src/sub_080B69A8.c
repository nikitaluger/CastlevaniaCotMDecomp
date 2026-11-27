extern s32 stepAnimationTrack(void *a, void *b);
extern void advanceMotion(void *a, s32 b);
extern void sub_080B72CC(void *a);

/* Updates an entity's animation and physics: advances the animation, integrates
 * motion with gravity, tweaks a sprite field, then clears the ground-contact
 * flag and runs the contact handler. */
void sub_080B69A8(u8 *self) {
    u8 *anim = *(u8 **)(self + 0x38);
    u8 *motion = *(u8 **)(self + 0x3C);

    stepAnimationTrack(anim, motion + 0x34);
    advanceMotion(motion, 0x4000);
    *(u16 *)(anim + 8) = (u16)(*(u16 *)(anim + 8) + 0xF400);
    sub_080B72CC(self);
}
