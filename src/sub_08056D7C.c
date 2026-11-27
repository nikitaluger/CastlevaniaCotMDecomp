extern s32 sub_08005910(s32, s32);
extern s32 fixedPointDistance(s32, s32);

/* Record the angle and distance from the owner's fixed-point position
 * (+0x4C/+0x5C) to the target's position (+8/+0xC) into the script state
 * block: the angle goes to +0x14 and the distance to +0x18. */
void sub_08056D7C(u8 *owner, u8 *target, u8 *script) {
    *(s32 *)(script + 0x14) = sub_08005910(*(s32 *)(owner + 0x5C) - *(s32 *)(target + 0xC), *(s32 *)(target + 8) - *(s32 *)(owner + 0x4C));
    *(s32 *)(script + 0x18) = fixedPointDistance(*(s32 *)(target + 8) - *(s32 *)(owner + 0x4C), *(s32 *)(target + 0xC) - *(s32 *)(owner + 0x5C));
}
