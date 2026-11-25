/* Initialize an effect part: set its mode field (+0x4C) to 1 and store the
 * given x/y/z coordinates at +0x5C, +0x6C and +0x7C. */
void sub_080BE810(void *part, s32 x, s32 y, s32 z) {
    *(s32 *)((u8 *)part + 0x4C) = 1;
    *(s32 *)((u8 *)part + 0x5C) = x;
    *(s32 *)((u8 *)part + 0x6C) = y;
    *(s32 *)((u8 *)part + 0x7C) = z;
}
