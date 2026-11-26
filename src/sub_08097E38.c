extern void postDisplaySprite(s32, s32, s32, s32, s32);

struct DmaRegs { vu32 src; vu32 dst; vu32 cnt; };

/* Copies size*16 bytes of palette data into palette RAM 0x05000180 + index*32,
 * immediately or through the asynchronous DMA helper, and when the palette
 * index is valid also mirrors size*8 bytes into the EWRAM palette cache at
 * 0x020214E0 + index*64 (two stores 0x80 apart). */
void sub_08097E38(s32 async, s32 src, s32 paletteIndex, s32 size) {
    if (async != 0) {
        postDisplaySprite(1, src, (paletteIndex << 5) + (s32)0x05000180, size << 5, 0x10);
    } else {
        struct DmaRegs *dma = (struct DmaRegs *)0x040000D4;
        dma->src = (u32)src;
        dma->dst = (u32)((paletteIndex << 5) + (s32)0x05000180);
        dma->cnt = (u32)((size << 4) | ((u32)0x80 << 24));
        (void)dma->cnt;
    }
    if (paletteIndex >= 0) {
        struct DmaRegs *dma = (struct DmaRegs *)0x040000D4;
        u8 *cacheBase;
        s32 cacheOffset;
        u32 control;
        dma->src = (u32)src;
        cacheOffset = paletteIndex << 6;
        cacheBase = (u8 *)0x020214E0;
        dma->dst = (u32)(cacheOffset + (s32)cacheBase);
        control = (u32)((size << 3) | ((u32)0x84 << 24));
        dma->cnt = control;
        (void)dma->cnt;
        dma->src = (u32)src;
        cacheBase += 0x80;
        dma->dst = (u32)(cacheOffset + (s32)cacheBase);
        dma->cnt = control;
        (void)dma->cnt;
    }
}
