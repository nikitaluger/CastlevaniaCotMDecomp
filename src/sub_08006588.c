extern u8 D_020227EC[];
extern vu32 D_040000D4[];

/* DMA one 16-colour palette bank per entry from the palette table into PALRAM:
 * for each i in [start,end], copy 0x20 bytes at table[i*0x48] + bank*0x20 to
 * 0x05000000 + i*0x20. */
void sub_08006588(s32 start, s32 end, s32 bank) {
    s32 i = start;
    if (i > end) return;
    {
        vu32 *dma = D_040000D4;
        u8 *table = D_020227EC;
        u8 *src = (u8 *)(i * 0x48 + ((bank << 5) + (u32)table));
        u32 dst = 0x05000000 + (i << 5);
        u32 cnt = 0x80000010;
        do {
            dma[0] = dst;
            dma[1] = (u32)src;
            dma[2] = cnt;
            dma[2];
            src += 0x48;
            dst += 0x20;
            i++;
        } while (i <= end);
    }
}
