/* Effect object geometry: +0x4C is the x position, +0x5C the y position and
 * +0x74 a flag set once the effect has been placed. */
struct EffectPlacement {
    u8 pad[0x4C];
    s32 x;
    u8 pad50[0x74 - 0x50];
    u8 placed;
};

/* Return whether the effect has been placed (flag byte at +0x74). */
u8 sub_080A02A4(struct EffectPlacement *effect) {
    return effect->placed;
}
