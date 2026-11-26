extern s32 D_080CA9A4[];

void sub_08008C78(u8 *arg0)
{
    register u8 *a = arg0;
    u16 sp0;
    vu16 *p = &sp0;
    u16 z = 0;
    s32 r7;
    s32 r2, r4;

    *p = z;
    {
        vu32 *dma = (vu32 *)0x040000D4;
        dma[0] = (u32)p;
        {
            s32 offset = *(s32 *)(a + 0x14) * 0x140 + 0x1C;
            dma[1] = (u32)a + offset;
        }
        dma[2] = 0x810000A0;
        (void)dma[2];
    }
    r7 = 0;

    r2 = *(s32 *)(a + 0x0C);
    r4 = r2 + D_080CA9A4[0];
    if (r2 > 0xA0) return;
    {
        s32 *table = D_080CA9A4;
        while (1) {
            s32 r3, r5;
            do { if (r4 > 0xA0) r4 = 0xA0;
            r3 = r2;
            r5 = r7 + 1; } while (0);
            if (r3 < r4) {
                u8 *dst = a + 0x1C;
                do {
                    s32 shifted = r3 * 2;
                    s32 row = *(s32 *)(a + 0x14) * 0x140;
                    u16 *out = (u16 *)(dst + (shifted + row));
                    s32 value = *(s32 *)(a + 0x0C);
                    value += r7;
                    value -= r3;
                    *out = value;
                    r3++;
                } while (r3 < r4);
            }
            r7 = r5;
            if (r5 > 0xF) break;
            r2 = r4;
            r4 = *(s32 *)(a + 0x0C) + table[r5];
            if (r2 > 0xA0) break;
        }
    }
}
