extern void sub_0806D8E4(void *);
extern void sub_0808B4C8(void);

inline u32 shl2(s32 x) { return (u32)x << 2; }

void sub_08007EF8(void) {
    s32 sp0;
    u8 *base = (u8 *)0x02025358;
    s32 z5 = 0;
    vu32 *dma = (vu32 *)0x040000D4;
    u8 *p;
    s32 off;
    s32 z4;
    u32 i, j;

    sp0 = z5;
    dma[0] = (u32)&sp0;
    dma[1] = 0x02025FF0;
    dma[2] = 0x85000637;
    (void)dma[2];

    base[0x10] = 0xFF;
    base[0x1A] = base[0x0B];
    p = base + 0xA6;
    {
        s32 one = 1;
        *p = one;
        p += 5; *p = one;
        p += 0xF; *p = one;

        z4 = 0;
        *(u16 *)(base + 0x3CE) = one;
        *(u16 *)(base + shl2(0xF3)) = 2;
        *(u16 *)(base + shl2(0xF4)) = 0x100;
        *(u16 *)(base + 0x3D2) = 0x200;

        off = shl2(0xC3);
        *(u16 *)(base + off) = one;
        off += 9; base[off] = 1;
        off -= 1; base[off] = 1;
    }
    off -= 0x40;
    sub_0806D8E4(base + off);

    off = shl2(0xBA);
    base[off] = z4;
    off += 0x28;
    *(u32 *)(base + off) = z5;
    off += 0xCF;
    base[off] = z4;

    if (*(s16 *)(base + 0x9C) == 2) {
        u8 *row;
        off = shl2(0xC7);
        row = base + off;
        for (i = 0; i <= 1; i++) {
            u8 *q = row + i * 10;
            for (j = 0; j <= 9; j++)
                *q++ = 1;
        }
    }
    if (base[0x0C] != 0) {
        sub_0808B4C8();
    }
}
