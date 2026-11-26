extern u16 D_080CE5E8[];

void sub_08019ED4(void *arg0, void *arg1) {
    u8 *r3 = *(u8 **)((u8 *)arg0 + 0x3C);
    u16 *r2 = D_080CE5E8;
    u16 v = *(u16 *)((u8 *)arg1 + 0x28);
    u16 *dst_1;
    u16 *dst_2;
    u16 *dst_3;
    u16 *dst_4;
    switch (v) {
    case 0x2D: r2 += 8; break;
    case 0x2E: r2 += 4; break;
    }
    do { dst_1 = (u16 *)*(volatile u32 *)((*(u8 **)((u8 *)arg0 + 0x3C)) + 0x28); } while (0);
    dst_1[3] = r2[0];
    dst_2 = (u16 *)*(volatile u32 *)((*(u8 **)((u8 *)arg0 + 0x3C)) + 0x28);
    dst_2[4] = r2[1];
    dst_3 = (u16 *)*(volatile u32 *)((*(u8 **)((u8 *)arg0 + 0x3C)) + 0x28);
    dst_3[5] = r2[2];
    dst_4 = (u16 *)*(volatile u32 *)((*(u8 **)((u8 *)arg0 + 0x3C)) + 0x28);
    dst_4[6] = r2[3];
}
