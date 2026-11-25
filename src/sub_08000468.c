void sub_080BFD7C(void);
void sub_080BEAB0(void);

struct S {
    u32 flags;
    u32 frameCount;
    u8 pad1[0xC - 8];
    u16 curBuffer;
    u16 prevBuffer;
    u8 pad2[0x12 - 0x10];
    u16 swapCounter;
    u8 pad3[0x53C - 0x14];
    u32 dma0Src;
    u32 dma0Dst;
    u32 dma0Cnt;
};
extern struct S D_02021E90;

/* Periodic sound-engine tick: acknowledge a finished DMA0 transfer, advance
 * the frame/buffer counters (swapping the mixing buffers on wrap), start the
 * next DMA0 transfer when requested, reload a timer, then run the tail hook. */
void sub_08000468(void) {
    volatile struct S *audio;
    struct S *audioNV;
    u16 dmaCtrl;
    u16 bufferIndex;
    u32 *dmaParams;
    volatile u32 *dma;

    sub_080BFD7C();
    audio = &D_02021E90;
    if (audio->flags & (0x80u << 21)) {
        volatile u16 *dma16 = (volatile u16 *)0x040000B0;
        dmaCtrl = dma16[5];
        dmaCtrl = (u16)(((u32)dmaCtrl << 17) >> 17);
        dma16[5] = dmaCtrl;
        dma16[5];
        audio->flags &= 0xEFFFFFFF;
    }
    audio->frameCount += 1;
    audio->swapCounter = audio->swapCounter + 1;
    if (audio->swapCounter == 0) {
        audioNV = (struct S *)audio;
        bufferIndex = audioNV->curBuffer;
        audioNV->prevBuffer = bufferIndex;
        audioNV->curBuffer = bufferIndex ^ 1;
    }
    if (audio->flags & (0x80u << 22)) {
        dmaParams = (u32 *)&audio->dma0Src;
        dma = (volatile u32 *)0x040000B0;
        dma[0] = dmaParams[0];
        dma[1] = dmaParams[1];
        dma[2] = dmaParams[2];
        dma[2];
        audio->flags |= (0x80u << 21);
    }
    *(volatile u32 *)0x04000104 = 0;
    *(volatile u32 *)0x04000104 = 0x00C1FACC;
    sub_080BEAB0();
}
