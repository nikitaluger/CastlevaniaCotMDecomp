s32 sub_08005820(s32);
void sub_080AAC20(s32, s32, s32);

/* Spawn eight objects in two groups of four (flags 0 and 1), each placed at
 * a randomized coordinate offset from a fixed base. */
void sub_080AAC58(void) {
    u32 i;
    s32 offset;
    for (i = 0; i < 4; i++) {
        offset = sub_08005820(0x1B00000) + 0x280000;
        sub_080AAC20(0, offset, 0x200000);
    }
    for (i = 0; i < 4; i++) {
        offset = sub_08005820(0x1B00000) + 0x280000;
        sub_080AAC20(1, offset, 0x200000);
    }
}
