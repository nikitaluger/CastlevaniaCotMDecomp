extern void sub_08060C74(u8, u8, u8, void *, void *);
extern void sub_08060D34(void);
extern void *D_086711E8[];

// Loads a 2bpp graphic into the work buffer at 0x02023248: ids 0-1 fill it with
// a flat nibble-duplicated palette pattern, other ids decompress a tile image
// from the D_086711E8 table. Then requests the DMA copy and advances the
// destination pointer/state counters.
void sub_08060A50(u16 gfxId) {
    u16 id = gfxId;
    u32 i;
    u8 *outBuf;
    u8 *patternSrc;

    switch (id) {
    case 0:
    case 1:
        i = 0;
        outBuf = (u8 *)0x02023248;
        patternSrc = (u8 *)(0x81 + (u32)outBuf);
        do {
            u8 *dstByte = (u8 *)(i + (u32)outBuf);
            u32 v = *patternSrc;
            *dstByte = (v << 4) | v;
            i++;
        } while (i <= 0x1F);
        break;
    default: {
        void **gfxTable = D_086711E8;
        s32 tableIndex = (s32)id - 2;
        void *src = gfxTable[tableIndex];
        sub_08060C74(4, 8, 0, src, (void *)0x02023248);
        break;
    }
    }
    if (id != 0) sub_08060D34();
    {
        u32 state = (u32)0x02021E90;
        *(u8 *)(state + 0x1443) += 1;
        *(s32 *)(state + 0x1448) += 0x20;
    }
}
