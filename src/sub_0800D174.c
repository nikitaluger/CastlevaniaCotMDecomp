void sub_08061F88(s32);
void sub_080C31E4(void *, void *, s32);

/* Loads tile graphics into VRAM (0x06016000) and two 64-byte palettes into
 * palette RAM (0x05000380/0x050003A0) with three DMA copies, services pending
 * VBlank work, clears a byte flag in the object, then calls the callback held
 * in the pointer table at 0x08671BB0 with (obj+0x18, obj+0x22). */
void sub_0800D174(void *arg0) {
    u8 *obj = arg0;
    vu32 *dma = (vu32 *)0x040000D4;
    s32 dmaReadback;
    dma[0] = 0x084548A4;
    dma[1] = 0x06016000;
    dma[2] = 0x80000DE0;
    dmaReadback = dma[2];
    dma[0] = 0x08453F20;
    dma[1] = 0x05000380;
    dma[2] = 0x80000010;
    dmaReadback = dma[2];
    dma[0] = 0x08453F40;
    dma[1] = 0x050003A0;
    dma[2] = 0x80000010;
    dmaReadback = dma[2];
    sub_08061F88(dmaReadback);
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = 0;
    {
        void **callbackTable;
        callbackTable = (void **)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, *callbackTable);
    }
}
