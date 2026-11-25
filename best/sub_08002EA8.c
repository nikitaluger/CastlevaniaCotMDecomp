void sub_08002EA8(void)
{
    u32 *base = (u32 *)0x02021E90;
    u32 *flagp = base + 0x156;
    u32 val = *flagp;
    u16 lo = *(u16 *)flagp;
    u32 *b = base;

    if (lo != 0 && (val & 0xFFFF0000) != 0)
    {
        vu32 *dma = (vu32 *)0x040000D4;
        dma[0] = (u32)(b + 0x157);
        dma[1] = 0x05000000;
        dma[2] = 0x80000200;
    }
    else
    {
        u32 *base2 = b;
        u32 *flagp2 = base2 + 0x156;
        u32 val2 = *flagp2;
        u16 lo2 = *(u16 *)flagp2;
        if (lo2 != 0)
        {
            vu32 *dma = (vu32 *)0x040000D4;
            dma[0] = (u32)(base2 + 0x157);
            dma[1] = 0x05000000;
            dma[2] = 0x80000100;
        }
        else if ((val2 & 0xFFFF0000) != 0)
        {
            vu32 *dma = (vu32 *)0x040000D4;
            dma[0] = (u32)(b + 0x1D7);
            dma[1] = 0x05000200;
            dma[2] = 0x80000100;
        }
    }
}
