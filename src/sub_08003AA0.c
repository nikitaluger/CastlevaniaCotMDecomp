extern u32 D_020230F0;
extern u32 D_040000D4;

/* Clear 0x40 words at D_020230F0: set up DMA3 to fill from a zero on the stack
 * and return the control register read back. */
s32 sub_08003AA0(void)
{
    s32 zero = 0;
    volatile s32 *dma = (volatile s32 *)0x040000D4;
    dma[0] = (s32)&zero;
    dma[1] = (s32)&D_020230F0;
    dma[2] = 0x85000040;
    return dma[2];
}
