void sub_0801BE64(u16 *arg0, s16 arg1) {
    s32 t = (s32)arg1 + (s32)*arg0;
    *arg0 = (u16)t;
    if ((s16)t > 0x2328)
        *arg0 = 0x2328;
}
