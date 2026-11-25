extern void sub_08097DF8(s32);

/* Work area: +0x1334 holds the destination pointer for the DMA fill. */
struct GfxWorkArea {
    u8 pad[0x1334];
    u32 fillDest;
};
extern struct GfxWorkArea D_02021E90;

/* Fill the work area's destination buffer with the halfword 0x100 via a
 * 16-bit DMA, then upload the graphics sheet at 0x083FF548. */
void sub_080B31F4(void) {
    u16 fillValue;
    u16 *fillSrc = &fillValue;
    vu32 *dma;
    *fillSrc = 0x80 << 1;
    dma = (vu32 *)0x040000D4;
    dma[0] = (u32)fillSrc;
    dma[1] = D_02021E90.fillDest;
    dma[2] = 0x81001000;
    (void)dma[2];
    sub_08097DF8(0x083FF548);
}
