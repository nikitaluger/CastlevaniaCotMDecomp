s32 sub_080C2F20(s32, s32);
s32 sub_08000E98(s32, s32, s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

void sub_080083B0(void *arg0) {
    void *p3C;
    volatile u32 *dma;
    u16 *base;
    u16 *tmpBase;
    u32 mask;
    u32 i;
    u32 j;
    u32 next;
    u16 *ptr;
    u32 maxColor;

    p3C = *(void **)((u8 *)arg0 + 0x3C);
    dma = (volatile u32 *)0x040000D4;
    dma[0] = 0x08645884;
    tmpBase = (u16 *)((u8 *)p3C + 0x1C);
    dma[1] = (u32)tmpBase;
    dma[2] = 0x80000030;
    (void)dma[2];
    i = 0;
    base = tmpBase;
    maxColor = 0x1F;
    mask = 0x1F;
    do {
        u32 off;
        j = 0;
        off = i * 32;
        next = ++i;
        ptr = (u16 *)(off + (u32)base);
        do {
            u16 px16 = *ptr;
            u32 r = maxColor & px16;
            u32 v = (u32)px16 << 16;
            u32 g = mask & (v >> 21);
            u32 b = mask & (v >> 26);
            u32 dr;
            u32 dg;
            u32 db;
            u8 m;
            dr = maxColor - r;
            m = *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19);
            r = r + sub_080C2F20(dr * m, 0xC0);
            dg = maxColor - g;
            m = *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19);
            g = g + sub_080C2F20(dg * m, 0xC0);
            db = maxColor - b;
            m = *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19);
            b = b + sub_080C2F20(db * m, 0xC0);
            r &= mask;
            g &= mask;
            g <<= 5;
            r |= g;
            b &= mask;
            b <<= 10;
            r |= b;
            *ptr = (u16)r;
            ptr++;
            j = j + 1;
        } while (j <= 0x0F);
        i = next;
    } while (i <= 0x02);
    sub_08000E98(1, (s32)base, 0x05000000, 0x60, 0x10);
    {
        u32 idx = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *q = (u8 *)(idx + (u32)arg0);
        if (q[0x19] == 0xC0) {
            u32 *pp;
            q[0x19] = 0;
            pp = (u32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *pp);
        }
    }
}
