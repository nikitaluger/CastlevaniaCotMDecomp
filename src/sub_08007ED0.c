/* Clears 0xF4 words of EWRAM at 0x02025368 with a DMA3 fill from a zero word
 * on the stack; returns the control register read back. */
s32 sub_08007ED0(void) {
    s32 *dest = (s32 *)0x02025368;
    s32 zero = 0;
    volatile s32 *dma = (volatile s32 *)0x040000D4;
    dma[0] = (s32)&zero;
    dma[1] = (s32)dest;
    dma[2] = 0x850000F4;
    return dma[2];
}
