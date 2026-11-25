extern u16 D_080CE5E8[];

void sub_08019ED4(void *arg0, void *arg1) {
    u8 *r3 = *(u8 **)((u8 *)arg0 + 0x3C);
    u16 *r2 = D_080CE5E8;
    u16 v = *(u16 *)((u8 *)arg1 + 0x28);
    u16 *dst;
    switch (v) {
    case 0x2D: r2 += 8; break;
    case 0x2E: r2 += 4; break;
    }
    dst = (u16 *)*(volatile u32 *)(r3 + 0x28);
    dst[3] = r2[0];
    dst = (u16 *)*(volatile u32 *)(r3 + 0x28);
    dst[4] = r2[1];
    dst = (u16 *)*(volatile u32 *)(r3 + 0x28);
    dst[5] = r2[2];
    dst = (u16 *)*(volatile u32 *)(r3 + 0x28);
    dst[6] = r2[3];
}
