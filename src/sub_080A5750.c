/* Load compressed graphics into VRAM, DMA a companion data block into EWRAM,
 * then fill in the sprite-data header's flags and pointers. */
extern void decompressToVram(const void *, void *);

void sub_080A5750(void)
{
    volatile u32 *dma3;
    u8 *dest;
    u32 zero;

    decompressToVram((const void *)0x083DDABC, (void *)0x0600A000);
    decompressToVram((const void *)0x083DF734, (void *)0x0600C000);

    dma3 = (volatile u32 *)0x040000D4;

    dma3[0] = 0x083DD8BC;
    dma3[1] = 0x02023B2E;
    dma3[2] = 0x80000100;
    (void)dma3[2];

    dest = (u8 *)0x02023B2E;

    dma3[0] = 0x083DF534;
    dma3[1] = (u32)(dest + 0x800);
    dma3[2] = 0x80000100;
    (void)dma3[2];

    {
        u16 *flagsPtr = (u16 *)(dest + 0xFFFFF602);
        u16 flags = *flagsPtr & 0xBFFF;
        zero = 0;
        *flagsPtr = flags;
    }

    *(u32 *)(dest + 0xFFFFF606) = 0x083DCA1C;
    *(u32 *)(dest + 0xFFFFF60A) = 0x083DD3DC;
    *(u16 *)(dest + 0xFFFFF612) = 0x10;

    {
        u16 *flagsPtr = (u16 *)(dest + 0xFFFFF642);
        *flagsPtr &= 0xBFFF;
    }

    *(u32 *)(dest + 0xFFFFF646) = 0x083DF054;
    *(u32 *)(dest + 0xFFFFF64A) = zero;
    *(u16 *)(dest + 0xFFFFF652) = 0x10;
}
