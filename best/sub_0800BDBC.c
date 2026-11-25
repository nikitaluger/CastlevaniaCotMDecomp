struct S_DMA4 { u32 sad; u32 dad; u32 ctrl; };
extern volatile struct S_DMA4 D_040000D4;
extern u32 D_0866CC18[];
extern u32 D_0866CC24[];
void sub_08000E98(u32, void *, void *, u32, u32);

void sub_0800BDBC(u8 *arg0, void *arg1, void *arg2) {
    u8 *r4 = arg0;
    u8 *r3 = arg1;
    void *sp8 = arg2;
    void *spC = arg1;
    u32 sp4 = 0;
    u32 r2;
    u32 r5;
    u8 v;
    u32 t;

    D_040000D4.sad = (u32)&sp4;
    D_040000D4.dad = (u32)spC;
    D_040000D4.ctrl = 0x850000C0;
    (void)D_040000D4.ctrl;
    r2 = 0;
    do {
        if (r2 & 1) {
            if (*r4 != 0) {
                r5 = 0;
                v = *r4;
                t = ((u32)v - 1) << 4;
                do {
                    u32 m4 = (r5 >> 3) * 4;
                    u32 l2 = (r5 & 7) * 4;
                    *r3 = *(const u8 *)(*(const u32 *)((u8 *)D_0866CC18 + m4 + t) + l2);
                    r3 += 1;
                    *r3 = *(const u8 *)(*(const u32 *)((u8 *)D_0866CC18 + m4 + (((u32)*r4 - 1) << 4)) + l2 + 1);
                    r3 += 0x3D;
                    *r3 = *(const u8 *)(*(const u32 *)((u8 *)D_0866CC18 + m4 + (((u32)*r4 - 1) << 4)) + l2 + 2);
                    r3 += 1;
                    *r3 = *(const u8 *)(*(const u32 *)((u8 *)D_0866CC18 + m4 + (((u32)*r4 - 1) << 4)) + l2 + 3);
                    r3 -= 0x3B;
                    r5 += 1;
                } while (r5 <= 0x0F);
                t = ((u32)v - 1) << 4;
                r5 = 0;
                do {
                    u32 m4 = ((r5 >> 3) + 2) * 4;
                    u32 l2 = (r5 & 7) * 4;
                    *r3 = *(const u8 *)(*(const u32 *)((u8 *)D_0866CC18 + m4 + t) + l2);
                    r3 += 1;
                    *r3 = *(const u8 *)(*(const u32 *)((u8 *)D_0866CC18 + m4 + (((u32)*r4 - 1) << 4)) + l2 + 1);
                    r3 += 3;
                    r5 += 1;
                } while (r5 <= 0x0F);
                r3 -= 2;
            } else {
                r3 += 0x7E;
            }
        } else {
            if (*r4 != 0) {
                D_040000D4.sad = D_0866CC18[((u32)*r4 - 1) * 4];
                D_040000D4.dad = (u32)r3;
                D_040000D4.ctrl = 0x84000008;
                (void)D_040000D4.ctrl;
                r3 += 0x20;
                D_040000D4.sad = D_0866CC18[((u32)*r4 - 1) * 4 + 1];
                D_040000D4.dad = (u32)r3;
                D_040000D4.ctrl = 0x84000008;
                (void)D_040000D4.ctrl;
                r3 += 0x20;
                D_040000D4.sad = D_0866CC18[((u32)*r4 - 1) * 4 + 2];
                D_040000D4.dad = (u32)r3;
                D_040000D4.ctrl = 0x84000008;
                (void)D_040000D4.ctrl;
                r3 += 0x20;
                D_040000D4.sad = D_0866CC24[((u32)*r4 - 1) * 4];
                D_040000D4.dad = (u32)r3;
                D_040000D4.ctrl = 0x84000008;
                (void)D_040000D4.ctrl;
                r3 -= 0x1E;
            } else {
                r3 += 0x42;
            }
        }
        r4 += 1;
        r2 += 1;
    } while (r2 <= 7);
    sub_08000E98(1, spC, sp8, 0x300, 0x10);
}
