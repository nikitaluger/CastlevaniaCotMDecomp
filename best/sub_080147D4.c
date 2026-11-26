s32 sub_080147D4(u32 arg0) {
    u32 v;
    u32 temp;
    do { v = arg0 & 0xFFFF; } while (0);
    if (v == (0x80 << 7) || v == (0xC0 << 8))
        return 0;
    temp = (u32)(v + 0xFFFFBFFF);
    if (temp <= 0x7FFE)
        return -1;
    return 1;
}
