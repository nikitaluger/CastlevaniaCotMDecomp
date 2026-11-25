/* Clear the whole actor/entity pool with zeros via DMA3 fill:
 * D_03002E34 = pool base, D_03002694 = slot count, 0xB words (0x2C bytes) per slot. */
void sub_080035E4(void) {
    u32 zero = 0;
    volatile u32 *dma;
    zero = 0;
    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)&zero;
    dma[1] = *(u32 *)0x03002E34;
    {
        u32 entityCount = *(u32 *)0x03002694;
        dma[2] = (0xB * entityCount) | 0x85000000;
    }
    (void)dma[2];
}
