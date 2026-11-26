s32 sub_08098400(void) {
    u16 *p;
    u16 v;
    u16 temp;
    do { do { p = (u16 *)0x03000830; } while (0); } while (0);
    v = p[2] & 0xDFC0;
    if (v != 0x80 && v != 0xC0) return 0;
    do { do { do { temp = p[4]; } while (0); } while (0); } while (0);
    if (temp != 0) return 1;
    return 0;
}
