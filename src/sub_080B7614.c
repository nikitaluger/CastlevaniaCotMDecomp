/* Render work area: a flags word at +0x12E0 and a destination pointer at
 * +0x12F4. */
struct DmaWork {
    u8 pad[0x12E0];
    u16 flags;
    u8 pad2[0x12];
    u32 dest;
};
extern struct DmaWork D_02021E90;

/* Flag the pending render job, then clear 0x100 bytes at the work area's
 * destination with a 16-bit DMA fill and wait for it to finish. */
void sub_080B7614(void) {
    u16 zero;
    u16 *src = &zero;
    vu32 *dma;
    D_02021E90.flags |= 0x80 << 6;
    zero = 0;
    dma = (vu32 *)0x040000D4;
    dma[0] = (u32)src;
    dma[1] = D_02021E90.dest;
    dma[2] = 0x81000080;
    (void)dma[2];
}
