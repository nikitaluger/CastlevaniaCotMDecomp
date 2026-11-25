s32 sub_08001626(u16 *arg0, u32 arg1) {
    s32 v;
    s16 *pv;
    s32 mask;
    s32 r;
    v = arg1;
    mask = *arg0 & 0x3FFF;
    pv = (s16 *)&v;
    r = 0;
    if (pv[0] <= mask && mask <= pv[1]) r = 1;
    return r;
}
