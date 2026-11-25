extern u32 D_02021E90[];

void sub_080063D4(void *, void *);          /* LZ77-decompress to VRAM */
void sub_08097E38(u32, void *, u32, u32);   /* upload one palette */

/* Load the shared effect graphics: decompress the tile set at 0x0841DEE8 into
 * VRAM charblock 1, clear and decompress the effect's second tile set at the
 * VRAM slot kept in D_02021E90+0x12F4, then upload the palette at 0x0840E218
 * into palette slot 1. */
void sub_080B74F0(void) {
    u16 zero;
    u16 *zeroPtr;
    vu32 *dma;
    u32 dstOff;
    u32 vramDest;
    sub_080063D4((void *)0x0841DEE8, (void *)0x06004000);
    zeroPtr = &zero;
    *zeroPtr = 0;
    dma = (vu32 *)0x040000D4;
    dma[0] = (u32)zeroPtr;
    dstOff = 0x12F4;
    vramDest = *(u32 *)((u8 *)D_02021E90 + dstOff);
    dma[1] = vramDest;
    dma[2] = 0x81000400;
    (void)dma[2];
    sub_080063D4((void *)0x0841DDD0, (void *)vramDest);
    sub_08097E38(0, (void *)0x0840E218, 1, 1);
}
