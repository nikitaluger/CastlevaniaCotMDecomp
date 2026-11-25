struct EffectPart {
    u8 pad[0x4C];
    u8 mode;
};

/* Turn the effect/part object on (mode flag at +0x4C = 1). */
void sub_080B0900(struct EffectPart *part) {
    part->mode = 1;
}
