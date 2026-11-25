/* Upload the colours of a graphics sheet: DMA its 256 bytes of palette data
 * to palette RAM at 0x05000180, then copy the sheet's next two 128-byte colour
 * blocks into the palette-fade work area at 0x020214E0/0x02021560. */
void sub_08097DF8(s32 sheet) {
    vu32 *dma3 = (vu32 *)0x040000D4;
    u32 dest;
    u32 ctrl;
    dma3[0] = (u32)sheet;
    dma3[1] = 0x05000180;
    dma3[2] = 0x80000040;
    (void)dma3[2];
    dma3[0] = (u32)sheet;
    dest = 0x020214E0;
    dma3[1] = dest;
    ctrl = 0x84000020;
    dma3[2] = ctrl;
    (void)dma3[2];
    dma3[0] = (u32)sheet;
    dest += 0x80;
    dma3[1] = dest;
    dma3[2] = ctrl;
    (void)dma3[2];
}
