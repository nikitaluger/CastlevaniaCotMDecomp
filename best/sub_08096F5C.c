s32 sub_08096F5C(void) {
    // Check if the 16-bit signed value at 0x020279E8 is equal to 0x0B (11 decimal).
    if (*(s16 *)0x020279E8 == 0xB) {
        return 1;
    }
    return 0;
}
