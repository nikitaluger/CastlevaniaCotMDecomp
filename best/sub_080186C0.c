void sub_080186C0(u16 *a, s16 b) {
    s32 v = *a + b;
    *a = (u16)v;
    if ((s16)v > 0x2328) {
        *a = 0x2328;
    }
}
