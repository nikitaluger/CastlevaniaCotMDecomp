void sub_080C02B0(s32 a, void *arg1) {
    u8 *p = (u8*)arg1;
    u8 v;
    u8 x;
    p[0x16] = 0;
    p[0x1A] = 0;
    v = p[0x18];
    if (v == 0) x = 0x0C; else x = 0x03;
    p[0] = p[0] | x;
}

u8 sub_080C02CC(s32 a, void *arg1) {
    u8 **pp = (u8**)((u8*)arg1 + 0x40);
    u8 *p = *pp;
    *pp = p + 1;
    return *p;
}

void sub_080C02D8(s32 a, void *arg1) {
    /* placeholder */
}
