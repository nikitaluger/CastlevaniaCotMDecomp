extern u8 D_02025368[];
extern u32 D_0866CF8C[];
extern void sub_080063D4(u32, u32);
extern void sub_08000E98(u32, u32, u32, u32, u32);
extern void sub_0800EB44(u32, u32, u32);

void sub_0800F4D4(u8 a0, u8 a1, u16 a2) {
    u16 v = a2;
    u16 v2 = a2;
    u8 *fb = D_02025368;
    if (a0 == 0) {
        u32 idx = a1 - 1;
        u8 *pf = fb + 0x316;
        if (*(pf + idx) != 0) {
            u32 src = D_0866CF8C[idx];
            u32 dst = ((u32)(v2 + 0x80) << 5) + 0x06008000;
            sub_080063D4(src, dst);
            sub_08000E98(1, dst, ((u32)v << 5) + 0x06008000, 0x100, 0x10);
        } else {
            sub_0800EB44(0x812A, v2, 0x100);
        }
    } else {
        u32 idx = a1 - 1;
        u8 *pf = fb + 0x30C;
        if (*(pf + idx) != 0) {
            u32 src = D_0866CF8C[idx + 10];
            u32 dst = ((u32)(v2 + 0x80) << 5) + 0x06008000;
            sub_080063D4(src, dst);
            sub_08000E98(1, dst, ((u32)v << 5) + 0x06008000, 0x100, 0x10);
        } else {
            sub_0800EB44(0x812A, v2, 0x100);
        }
    }
}
