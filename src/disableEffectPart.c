struct EffectPart {
    u8 pad[0x4C];
    u8 mode;
};

/* Turn the effect/part object off (mode flag at +0x4C = 0). */
void disableEffectPart(struct EffectPart *part) {
    part->mode = 0;
}
