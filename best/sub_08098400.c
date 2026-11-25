s32 sub_08098400(void) {
    u16 *p = (u16 *)0x03000830;
    u16 v = p[2] & 0xDFC0;
    if (v != 0x80 && v != 0xC0) return 0;
    if (p[4] != 0) return 1;
    return 0;
}
