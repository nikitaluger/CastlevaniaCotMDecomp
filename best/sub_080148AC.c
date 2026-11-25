s32 sub_080148AC(void *arg0, s32 arg1) {
    if (*(u16 *)((u8 *)arg0 + 2) & 0x10)
        return -arg1;
    return arg1;
}

void sub_080269D4(void *arg0, u16 arg1) {
    u32 *base = *(u32 **)((u8 *)arg0 + 0x3C);
    u32 *p = base + 0x1A;
    s32 i = 4;
    u16 mask = (u16)(~arg1);
    do {
        u32 *q = (u32 *)*p;
        if (q != 0) {
            *(u16 *)((u8 *)q + 0x64) &= mask;
        }
        p++;
        i--;
    } while (i >= 0);
}

s32 sub_08026A04(void *arg0) {
    u32 *base = *(u32 **)((u8 *)arg0 + 0x3C);
    s32 i = 0;
    s32 mask = 0x20;
    u32 *p = base + 0x1A;
    do {
        u32 *q = (u32 *)*p;
        if (q != 0) {
            if ((*(u16 *)((u8 *)q + 0x64) & mask) == 0)
                return 0;
        }
        p++;
        i++;
    } while (i <= 4);
    return 1;
}

s32 sub_080147D4(u32 arg0) {
    u32 v = arg0 & 0xFFFF;
    if (v == 0x4000 || v == 0xC000)
        return 0;
    if ((u32)(v + 0xFFFFBFFF) > 0x7FFE)
        return 1;
    return -1;
}
