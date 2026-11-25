/* Clear a block of the global workspace with a filling DMA (fixed zero
 * source), then restore one saved byte in the state block at 0x02025358. */
void sub_08007FE0(void) {
    vu8 *state = (vu8 *)0x02025358;
    s32 zero = 0;
    vu32 *dma = (vu32 *)0x040000D4;

    dma[0] = (u32)&zero;
    dma[1] = 0x02025FF0;
    dma[2] = 0x85000637;
    dma[2];
    state[0x1A] = state[0x0B];
}
