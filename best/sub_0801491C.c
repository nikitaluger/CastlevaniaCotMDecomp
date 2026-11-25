extern u8 D_02025FF0[];

s32 sub_0801491C(s32 arg0) {
    s32 v = *(s32 *)(D_02025FF0 + 0x1750) - arg0;
    if (v < 0)
        v = -v;
    return v;
}
