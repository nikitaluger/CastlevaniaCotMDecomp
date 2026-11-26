extern void decompressToVram(void *, void *);
extern void sub_08097DF8(void *);
extern u32 gCameraState[];

/* Load a sprite graphics sheet: decompress its tiles into VRAM at 0x0600E000,
 * fill the 16 KB block they cover with the transparent colour 0x8080 through
 * DMA3, then upload the sheet's palette/OAM data. */
void sub_0809C6EC(void)
{
    u16 clearColor;
    u16 *clearSrc;
    vu32 *dma3;
    u32 dstOffset;
    u32 vramDst;

    decompressToVram((void *)0x083C71A4, (void *)0x0600E000);
    clearSrc = &clearColor;
    *clearSrc = 0x8080;
    dma3 = (vu32 *)0x040000D4;
    dma3[0] = (u32)clearSrc;
    dstOffset = 0x12F4;
    vramDst = *(u32 *)((u8 *)gCameraState + dstOffset);
    dma3[1] = vramDst;
    dma3[2] = 0x81002000;
    (void)dma3[2];
    sub_08097DF8((void *)0x083C6B84);
}
