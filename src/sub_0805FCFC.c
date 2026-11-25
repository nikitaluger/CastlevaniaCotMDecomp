extern u8 D_02021E90[];
extern void sub_0805FDF0(void);
extern void sub_0805FE28(s32, s32);
extern void sub_0805FE8C(s32, s32, s32);
extern void sub_080063D4(u32 *, void *);
extern void sub_08061048(s32);
extern void sub_08061084(void);
extern void sub_080610D0(void);

/* Clears graphics state, loads tiles into VRAM and fills palette memory with DMA. */
void sub_0805FCFC(void) {
    u8 *gfxState = D_02021E90;
    u16 fillValue;
    u16 *vramFlags;
    u32 zero;
    u32 fillControl;
    u8 *flagByte = gfxState + 0x1458;

    zero = 0;
    *flagByte = zero;
    {
        u32 off = 0x145A;
        *(u16 *)(gfxState + off) = zero;
        gfxState[off + 3] = zero;
    }
    sub_0805FDF0();
    sub_0805FE28(0, 2);
    sub_0805FE8C(0, 1, 2);
    vramFlags = (u16 *)(gfxState + 0x1262);
    {
        u32 dest = 0x06000C80 + ((*vramFlags & 0x1F00) << 3);
        vu32 *dma = (vu32 *)0x040000D4;
        dma[0] = 0x08442650;
        dma[1] = 0xA0 << 19;
        dma[2] = 0x80000010;
        (void)dma[2];
        sub_080063D4((u32 *)0x08442670, (void *)dest);
    }
    fillValue = zero;
    {
        vu32 *dma = (vu32 *)0x040000D4;
        dma[0] = (u32)&fillValue;
        dma[1] = (0xC0 << 19) + ((*vramFlags & 0xC) << 12);
        fillControl = 0x81000010;
        dma[2] = fillControl;
        sub_08061048(dma[2]);
    }
    sub_08061084();
    sub_080610D0();
    {
        u16 *fillSrc = &fillValue;
        vu32 *dma = (vu32 *)0x040000D4;
        u8 paletteIndex = gfxState[0x1439];
        *fillSrc = paletteIndex | (paletteIndex << 4);
        dma[0] = (u32)fillSrc;
        dma[1] = 0x06000020 + ((*vramFlags & 0xC) << 12);
        dma[2] = fillControl;
        (void)dma[2];
    }
}
