extern u8 gCameraState[];

/* Initialize the 16-byte node pool in work RAM: 64 nodes occupy
 * gCameraState+0x128..+0x518 and are linked (next at +0xC) into one free list
 * whose head pointer lives at +0x528; the four list-head words at +0x52C are
 * then DMA-cleared. */
void sub_08000D6C(void) {
    u32 prev = 0;
    u8 *pool = gCameraState;
    u32 zero;
    u32 headSlot;
    u32 firstSlot;
    u32 slot;
    u32 listHeads;
    u32 limit;
    volatile u32 *dma;

    headSlot = (u32)&pool[0xA5 << 3];
    firstSlot = (u32)&pool[0x94 << 1];
    *(u32 *)headSlot = firstSlot;
    slot = (u32)&pool[0xA3 << 3];
    listHeads = (u32)&pool[(0xA3 << 3) + 0x14];
    if (slot >= firstSlot) {
        limit = firstSlot;
        do {
            *(u32 *)(slot + 0xC) = prev;
            prev = slot;
            slot -= 0x10;
        } while (slot >= limit);
    }
    zero = 0;
    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)&zero;
    dma[1] = listHeads;
    dma[2] = 0x85000004;
    (void)dma[2];
}
