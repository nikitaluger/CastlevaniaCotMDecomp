struct EffectPart {
    u8 pad[0x4C];
    u8 mode;
    u8 pad2[3];
    u8 state;
};

/* Set the secondary state byte at +0x50 of an effect/part object
 * (0 = idle/off, 1 = finished, 2 = triggered). */
void sub_080BE8C8(struct EffectPart *part, u8 state) {
    part->state = state;
}
