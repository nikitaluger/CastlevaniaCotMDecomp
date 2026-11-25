extern s32 sub_080113A8(void *a, void *b);
extern void sub_0801165C(void *a, s32 b);
extern void sub_080B72CC(void *a);

/* Updates an entity's animation and physics: advances the animation, integrates
 * motion with gravity, tweaks a sprite field, then clears the ground-contact
 * flag and runs the contact handler. */
void sub_080B69A8(u8 *self) {
    u8 *anim = *(u8 **)(self + 0x38);
    u8 *motion = *(u8 **)(self + 0x3C);

    sub_080113A8(anim, motion + 0x34);
    sub_0801165C(motion, 0x4000);
    *(u16 *)(anim + 8) = (u16)(*(u16 *)(anim + 8) + 0xF400);
    sub_080B72CC(self);
}
