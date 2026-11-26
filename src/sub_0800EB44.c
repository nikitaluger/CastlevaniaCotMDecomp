extern u8 gCameraState[];

void postDisplaySprite(s32, s32, s32, s32, s32);
s32 setLayerTilemap(s32, u16);
s32 sub_0805FEC8(u16);

/* Zero-fill a VRAM tile block with DMA3: derive the source address from the
 * tile row and the VRAM bank bits, mirror it to the opposite 32K bank, then
 * record the address, set the palette colour and schedule the copy. */
void sub_0800EB44(u16 color, s32 tileRow, u32 size) {
    u8 *base;
    volatile u32 *dma;
    s16 zeroWord;
    u16 *pa;
    u32 rowBits;
    u32 row;
    u32 vramLimit;
    u32 vramAddr;
    s32 mirror;
    u32 fillAddr;
    u32 ctrlRead;

    rowBits = ((u32)tileRow << 22) >> 22;
    row = rowBits;
    base = gCameraState;
    vramAddr = ((*(u16 *)(base + 0x1262) & 0xC) << 12) + (row << 5) + (0xC0 << 19);
    vramLimit = 0x06007FFF;
    mirror = 0xFFFFFC00;
    if (vramAddr <= vramLimit) mirror = 0x400;
    pa = &zeroWord;
    *pa = 0;
    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)pa;
    fillAddr = vramAddr + (mirror << 5);
    dma[1] = fillAddr;
    dma[2] = (size >> 1) | (0x81 << 24);
    ctrlRead = dma[2];
    setLayerTilemap(0, (u16)(row + mirror));
    sub_0805FEC8(color);
    postDisplaySprite(1, fillAddr, vramAddr, size, 0x10);
}
