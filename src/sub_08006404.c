extern vu16 D_0200E280;
extern vu32 D_0200E284;
extern vu8 D_0200E288;
extern vu16 D_03000830;

/* Restore the saved graphics state from the 0x02021E90 work buffer, then use
 * DMA3 to copy a VRAM block back to 0x0200E290 and several object-tile blocks
 * to the buffers around 0x0201E290. */
void sub_08006404(void) {
    u32 gfxSrc;
    u8 *gfxDest;
    vu32 *stateWordPtr;
    vu8 *stateBytePtr;
    vu32 *dma;

    D_0200E280 = D_03000830;
    stateWordPtr = &D_0200E284;
    gfxSrc = 0x02021E90;
    *stateWordPtr = *(vu32 *)(gfxSrc + 0x125C);
    stateBytePtr = &D_0200E288;
    *stateBytePtr = *(vu8 *)(gfxSrc + (0x9B << 5));

    dma = (vu32 *)0x040000D4;
    dma[0] = 0xC0 << 19;
    dma[1] = (u32)0x0200E290;
    dma[2] = 0x80008000;
    (void)dma[2];

    dma[0] = gfxSrc + 0x1260;
    gfxDest = (u8 *)0x0201E290;
    dma[1] = (u32)gfxDest;
    dma[2] = 0x84000010;
    (void)dma[2];

    dma[0] = gfxSrc + ((0x9B << 5) - 0xC0);
    dma[1] = (u32)(gfxDest + 0x40);
    dma[2] = 0x84000010;
    (void)dma[2];

    dma[0] = gfxSrc + ((0x9B << 5) - 0xC0 + 0x40);
    dma[1] = (u32)(gfxDest + 0x80);
    dma[2] = 0x84000010;
    (void)dma[2];

    dma[0] = gfxSrc + ((0x9B << 5) - 0xC0 + 0x80);
    gfxDest += 0xC0;
    dma[1] = (u32)gfxDest;
    dma[2] = 0x84000010;
    (void)dma[2];

    dma[0] = gfxSrc + (0xA3 << 5);
    dma[1] = (u32)0x0201E390;
    dma[2] = 0x84000003;
    (void)dma[2];
}
