/* Effect object geometry: +0x4C is the x position, +0x5C the y position and
 * +0x74 a flag set once the effect has been placed. */
struct EffectPlacement {
    u8 pad[0x4C];
    s32 x;
    u8 pad50[0x74 - 0x50];
    u8 placed;
};

/* Place the effect at the given x position and mark it as placed. */
void sub_080A0288(struct EffectPlacement *effect, s32 x) {
    effect->placed = 1;
    effect->x = x;
}
