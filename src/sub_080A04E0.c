/* Load a graphics sheet: decompress tiles into VRAM, fill a VRAM block with
 * 0x8080 through DMA3, copy tile data over it, then upload its palette. */
extern void sub_080063D4(void *, void *);
extern void sub_08097DF8(void *);
extern u8 D_02021E90[];

void sub_080A04E0(void)
{
    u16 fillValue;
    u16 *fillSrc;
    vu32 *dma3;
    u32 vramOff;
    u32 vramDst;

    sub_080063D4((void *)0x083C71A4, (void *)0x0600E000);
    fillSrc = &fillValue;
    *fillSrc = 0x8080;
    dma3 = (vu32 *)0x040000D4;
    dma3[0] = (u32)fillSrc;
    vramOff = 0x12F4;
    vramDst = *(u32 *)(D_02021E90 + vramOff);
    dma3[1] = vramDst;
    dma3[2] = 0x81002000;
    (void)dma3[2];
    dma3[0] = (u32)0x083C6BA4;
    dma3[1] = vramDst;
    dma3[2] = 0x80000080;
    (void)dma3[2];
    sub_08097DF8((void *)0x083C6B84);
}
