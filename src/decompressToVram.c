extern void sub_080C2F2C(u32 *src, void *dst);

/* Decompress LZ77 data from src into a staging buffer, then DMA the result to
 * dst (VRAM). The saved LZ77 header supplies the transfer size, and setting
 * bit 31 of the control word starts the copy. */
void decompressToVram(u32 *src, void *dst) {
    u32 header = *src;
    sub_080C2F2C(src, (void *)0x0200A280);
    {
        vu32 *dma = (vu32 *)0x040000D4;
        dma[0] = 0x0200A280;
        dma[1] = (u32)dst;
        dma[2] = (header >> 9) | 0x80000000;
        (void)dma[2];
    }
}
