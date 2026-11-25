void sub_080C2E4C(u8 *dst, s32 n) {
    u8 *p = dst;
    s32 orig = n;
    n = n - 1;
    if (orig != 0) {
        do {
            *p = 0;
            p += 1;
        } while (n-- != 0);
    }
}
