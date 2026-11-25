/* Effect object parameters: +0x6C is the effect state (see sub_080A0204),
 * +0x70 and +0x74 are two script-supplied effect parameters. */
struct EffectParams {
    u8 pad[0x70];
    u8 param70;
    u8 pad71[3];
    u8 param74;
};

/* Reset the effect's two parameter bytes to zero. */
void sub_080A0294(struct EffectParams *effect) {
    effect->param74 = 0;
    effect->param70 = 0;
}
