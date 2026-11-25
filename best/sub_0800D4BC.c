extern void *sub_08001480(s32, s32);
extern void sub_0800EC20(s32);
extern void sub_0800ECF8(void);
extern void sub_0800EDAC(s32);
extern void sub_0800EF3C(s32);
extern void sub_0800F040(void);
extern void sub_0800F104(void);
extern void sub_0800F1D8(u8, s32);
extern void sub_0800F3C8(u8, s32);
extern u8 D_02021E90[];
extern u8 D_020278D0[];

void sub_0800D4BC(s32 arg0) {
    u32 i;
    u8 *base;
    u8 *q;
    u8 *b2;
    void **slots;
    u32 z0;
    u32 z1;

    base = D_020278D0;
    q = base;
    q += 0x69;
    z0 = 0;
    *q = z0;
    i = 0;
    base += 0x48;
    for (; i <= 6; i++) {
        *(u32 *)base = z0;
        base += 4;
    }

    b2 = D_020278D0;
    slots = (void **)(b2 + 0x4C);
    for (i = 0; i <= 3; i++) {
        slots[i] = sub_08001480(arg0, 0x1B);
        *(u8 *)((u8 *)slots[i] + 0x3C) = 1;
        *(u8 *)((u8 *)slots[i] + 0x44) = i;
    }

    i = 0;
    b2 = D_020278D0;
    slots = (void **)(b2 + 0x5C);
    for (; i <= 1; i++) {
        slots[i] = sub_08001480(arg0, 0x1B);
        *(u8 *)((u8 *)slots[i] + 0x3C) = 3;
        *(u8 *)((u8 *)slots[i] + 0x44) = i;
    }

    z1 = 0;
    sub_0800F104();
    sub_0800F1D8(D_020278D0[0x6A], 0);
    sub_0800F1D8(D_020278D0[0x6A], 1);
    sub_0800F3C8(D_020278D0[0x69], 0);
    sub_0800F040();
    sub_0800EF3C(0xFF);

    D_02021E90[0xA3 << 5] = z1;
    D_02021E90[0x1464] = 0x60;
    D_02021E90[0x1462] = 0xF0;
    D_02021E90[0x1466] = 0x80;
    D_02021E90[0x1468] = 0x3F;
    D_02021E90[0x146A] = 0x3D;
    sub_0800ECF8();
    sub_0800EDAC(1);
    sub_0800EC20(0x060072B2);
}
