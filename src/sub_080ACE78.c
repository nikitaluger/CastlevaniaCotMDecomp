s32 sub_08005910(s32, s32);
s32 sub_080059DC(s32, s32);

/* Initialise a homing-state block: remember its owner, set its state to 4,
 * then record the angle and distance from the block's reference point
 * (+0x16C/+0x170) to the owner's position block (pos+8/pos+0xC). */
void sub_080ACE78(s32 owner, void *pos, void *state) {
    s32 dist;

    *(s32 *)((u8 *)state + 4) = owner;
    *(u8 *)((u8 *)state + 0x14) = 4;
    *(s32 *)((u8 *)state + 8) = sub_08005910(*(s32 *)((u8 *)pos + 0xC) - *(s32 *)((u8 *)state + 0x170), *(s32 *)((u8 *)pos + 8) - *(s32 *)((u8 *)state + 0x16C));
    dist = sub_080059DC(*(s32 *)((u8 *)state + 0x16C) - *(s32 *)((u8 *)pos + 8), *(s32 *)((u8 *)state + 0x170) - *(s32 *)((u8 *)pos + 0xC));
    *(s32 *)((u8 *)state + 0xC) = dist;
    *(s32 *)((u8 *)state + 0x10) = dist;
}
