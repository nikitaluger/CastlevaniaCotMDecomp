s32 sub_080147A4(u32 a, u32 b, u32 c) {
    u32 m = 0xFFFF;
    c &= m;
    a &= m;
    b &= m;
    if (a > b) {
        if (c >= a && c <= m) return 1;
        if (c <= b) return 1;
        return 0;
    } else {
        if (c >= a && c <= b) return 1;
        return 0;
    }
}
