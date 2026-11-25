extern u16 D_080CF4FC[];

void sub_08042900(void *arg0, void *arg1) {
    u8 *a1 = (u8 *)arg1;
    u16 *src = D_080CF4FC;
    int v = *(u16 *)((u8 *)arg0 + 0x28);
    u8 *dst;

    if (v == 0x10) goto _26;
    if (v > 0x10) goto _18;
    if (v == 0x0C) goto _22;
    goto _2C;
_18:
    if (v == 0x14) goto _2A;
    if (v == 0x1C) goto _2A;
    goto _2C;
_22:
    src += 4;
    goto _2C;
_26:
    src += 8;
    goto _2C;
_2A:
    src = (u16 *)0x080CF514;
_2C:
    dst = *(u8 *volatile *)(a1 + 0x28);
    *(u16 *)(dst + 6) = src[0];
    dst = *(u8 *volatile *)(a1 + 0x28);
    *(u16 *)(dst + 8) = src[1];
    dst = *(u8 *volatile *)(a1 + 0x28);
    *(u16 *)(dst + 0xA) = src[2];
    dst = *(u8 *volatile *)(a1 + 0x28);
    *(u16 *)(dst + 0xC) = src[3];
}
