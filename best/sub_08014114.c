extern u8 D_02025FF0[];
extern u8 D_02021E90[];

s32 sub_08014114(s32 x, s32 y, u16 w, u16 h, u16 lo, u16 hi) {
    u8 *base = D_02021E90;
    u8 *state = D_02025FF0;
    u8 *p0;
    u8 *p1;
    u32 off;
    s32 v0;
    s32 v1;
    s32 xmax;
    s32 ymax;

    off = (u32)(state[0x18A8] + 1) << 6;
    p0 = base + 0x1278;
    p1 = base + 0x127C;
    v0 = *(s32 *)(p0 + off);
    xmax = v0 + 0xF00000;
    v1 = *(s32 *)(p1 + off);
    ymax = v1 + 0xA00000;
    if (x + ((s32)h << 16) < v0) return 0;
    if (x + ((s32)w << 16) > xmax) return 0;
    if (y + ((s32)hi << 16) < v1) return 0;
    if (y + ((s32)lo << 16) <= ymax) return 1;
    return 0;
}
