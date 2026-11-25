s32 sub_080147D4(u32 arg0) {
    u32 v = arg0 & 0xFFFF;
    if (v == (0x80 << 7) || v == (0xC0 << 8))
        return 0;
    if ((u32)(v + 0xFFFFBFFF) <= 0x7FFE)
        return -1;
    return 1;
}
