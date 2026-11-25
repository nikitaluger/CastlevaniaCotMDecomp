/* Copy the entity's spawn parameters into its two sub-objects: X/Y into the
 * +0x3C object's +8/+0xC words, and the parameter at +0x6C (bias-adjusted and
 * truncated) into the +0x38 object's +8 halfword. */
void sub_080A9EC8(u8 *entity) {
    u8 *motion = *(u8 **)(entity + 0x38);
    u8 *state = *(u8 **)(entity + 0x3C);
    *(s32 *)(state + 8) = *(s32 *)(entity + 0x4C);
    *(s32 *)(state + 0xC) = *(s32 *)(entity + 0x5C);
    *(s16 *)(motion + 8) = *(s32 *)(entity + 0x6C) + ~0x3FFF;
}
