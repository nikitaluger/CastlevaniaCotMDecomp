s32 sub_08000BA4(u8 *arg0, u32 arg1) {
    u32 words = (arg1 + 3) >> 2;
    u32 bytes = words << 2;
    u8 *hdr = arg0 - 4;
    s32 size = *(s32 *)hdr >> 8;
    s32 remain;
    if ((u32)size < bytes)
        return -1;
    remain = (size - bytes) - 4;
    if (remain > 0) {
        u8 *next = hdr + (bytes + 4);
        *(volatile u8 *)next = 0;
        *(u32 *)next = *(volatile u8 *)next | ((u32)remain << 8);
        *(u32 *)hdr = *(volatile u8 *)hdr | (words << 10);
    }
    return *(s32 *)hdr >> 8;
}

extern void sub_080C0020(void *, s32);

void sub_080C0B70(void *arg0) {
    s32 v = *(s32 *)((u8 *)arg0 + 0x34);
    if (v == 0x68736D53) {
        u8 n;
        s32 p;
        *(s32 *)((u8 *)arg0 + 0x34) = v + 1;
        *(s32 *)((u8 *)arg0 + 4) |= 0x80000000;
        n = *(u8 *)((u8 *)arg0 + 8);
        p = *(s32 *)((u8 *)arg0 + 0x2C);
        if ((s32)n > 0) {
            do {
                sub_080C0020(arg0, p);
                n--;
                p += 0x50;
            } while ((s32)n > 0);
        }
        *(s32 *)((u8 *)arg0 + 0x34) = 0x68736D53;
    }
}

void sub_080C0DA0(u8 arg0) {
    u8 *r1;
    u8 v;
    switch (arg0) {
    case 1:
        r1 = (u8 *)0x04000063;
        *r1 = 8;
        r1 += 2;
        v = 0x80;
        break;
    case 2:
        r1 = (u8 *)0x04000069;
        *r1 = 8;
        r1 += 4;
        v = 0x80;
        break;
    case 3:
        r1 = (u8 *)0x04000070;
        v = 0;
        break;
    default:
        r1 = (u8 *)0x04000079;
        *r1 = 8;
        r1 += 4;
        v = 0x80;
        break;
    }
    *r1 = v;
}

void sub_080C1274(void *arg0, u16 arg1) {
    if (*(s32 *)((u8 *)arg0 + 0x34) == 0x68736D53) {
        s32 prod;
        *(u16 *)((u8 *)arg0 + 0x1E) = arg1;
        prod = (s32)arg1 * (s32)*(u16 *)((u8 *)arg0 + 0x1C);
        *(u16 *)((u8 *)arg0 + 0x20) = prod >> 8;
    }
}
