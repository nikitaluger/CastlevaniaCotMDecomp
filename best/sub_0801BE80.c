void sub_0801BE80(u16 *arg0, s16 arg1) {
    s32 v = (s32)*arg0 - (s32)arg1;
    *arg0 = (u16)v;
    if ((v << 16) <= 0x03E70000) {
        *arg0 = 0x3E8;
    }
}
