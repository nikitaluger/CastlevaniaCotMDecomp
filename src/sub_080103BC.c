extern u8 D_02025368[];
void sub_08010320(u8, u32);

/* Erase save slot `slot`: zero-fill the 0x3D0-byte save buffer (0xF4 words,
 * D_02025368) through DMA3, then write the empty block back to the slot. */
void sub_080103BC(u8 slot) {
    u32 *saveBlock = (u32 *)D_02025368;
    u32 zero = 0;
    vu32 *dma = (vu32 *)0x040000D4;
    dma[0] = (u32)&zero;
    dma[1] = (u32)saveBlock;
    dma[2] = 0x850000F4;
    sub_08010320(slot, dma[2]);
}
