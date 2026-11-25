struct EffectPart {
    u8 pad[0x4C];
    u8 mode;
};

/* Disable a linked effect/part object: clear its mode flag at +0x4C.
 * Twin of sub_080B71A4 for the second companion slot (motion+0x48 -> +0x10). */
void sub_080B7288(struct EffectPart *part) {
    part->mode = 0;
}
