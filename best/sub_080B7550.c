extern u8 D_02021E90[];
extern u8 D_02025FF0[];

void sub_080B7550(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *pb;
    u32 idx;
    if (arg0 == 0) {
        u8 *p = D_02021E90;
        u32 o = 0x97;
        o <<= 5;
        *(u16 *)(p + o) |= 0x2000;
        return;
    }
    {
        u8 *p = D_02021E90;
        u32 o = 0x97;
        o <<= 5;
        *(u16 *)(p + o) &= 0xDFFF;
        pb = D_02025FF0;
        pb += 0x18A8;
        idx = ((u32)*pb + 1) * 0x40;
        *(u16 *)(p + 0x1314) = (arg1 - ((*(u32 *)(p + o - 0x68 + idx) + 0x8000) & 0xFFFF0000)) >> 16;
        idx = ((u32)*pb + 1) * 0x40;
        *(u16 *)(p + 0x1316) = (arg2 - ((*(u32 *)(p + 0x127C + idx) + 0xFFFF8000) & 0xFFFF0000)) >> 16;
        *(u32 *)(p + 0x1308) = arg3;
        *(u32 *)(p + 0x130C) = arg3;
        *(u16 *)(p + 0x1318) = arg4;
    }
}
