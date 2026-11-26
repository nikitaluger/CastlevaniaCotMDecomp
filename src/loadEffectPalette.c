/* DMA-copy `src` into BG palette RAM at 0x05000300 (64 bytes), then into two
 * adjacent 128-byte blocks of IRAM starting at 0x020213E0, via DMA3. */
void loadEffectPalette(s32 src) {
    vu32 *dma = (vu32 *)0x040000D4;
    u32 dst;
    u32 ctrl;
    dma[0] = (u32)src;
    dma[1] = 0x05000300;
    dma[2] = 0x80000040;
    (void)dma[2];
    dma[0] = (u32)src;
    dst = 0x020213E0;
    dma[1] = dst;
    ctrl = 0x84000020;
    dma[2] = ctrl;
    (void)dma[2];
    dma[0] = (u32)src;
    dst += 0x80;
    dma[1] = dst;
    dma[2] = ctrl;
    (void)dma[2];
}

s32 sub_08097A48(void) {
    s16 v = *(s16 *)0x020279E8;
    if (v == 3) return 0;
    if (v == 4) return 1;
    return -1;
}

s32 sub_08098400(void) {
    u16 *p = (u16 *)0x03000830;
    u16 v = p[2] & 0xDFC0;
    if (v == 0x80 || v == 0xC0) {
        if (p[4] != 0) return 1;
    }
    return 0;
}

void sub_08098534(s32 arg0, u16 *arg1, u32 arg2) {
    u32 i = 0;
    u32 count = arg2 >> 1;
    u16 *tbl = (u16 *)0x081013AC;
    u16 *dst = arg1;
    if (count > 0) {
        do {
            u32 idx = (arg0 << 5) + ((i & 0xF) << 1);
            *dst &= *(u16 *)((u8 *)tbl + idx);
            dst++;
            i++;
        } while (i < count);
    }
}
