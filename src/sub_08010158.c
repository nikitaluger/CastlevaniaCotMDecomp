extern void sub_08010250(void);
extern void sub_0801026C(void);
extern void sub_08010320(u8);

/* Save-data setup: point at SRAM, read back its 16-byte header, and if it does
 * not carry the "DRACULA AGB" magic, clear and rebuild the save area, then
 * write out the eight default save blocks. */
void sub_08010158(void) {
    u32 zero;
    vu32 *dma3;
    u8 *magic;
    u32 block;

    *(vu32 *)0x02021E80 = 0xE0 << 20;
    sub_08010250();
    magic = (u8 *)0x02025358;
    if (*(u32 *)magic != 0x43415244 || *(u32 *)(magic + 4) != 0x20414C55 || (*(u32 *)(magic + 8) & 0xFFFFFF) != 0x424741) {
        zero = 0;
        dma3 = (vu32 *)0x040000D4;
        dma3[0] = (u32)&zero;
        dma3[1] = (u32)0x02025350;
        dma3[2] = 0x850000FC;
        (void)dma3[2];
        while (dma3[2] & (u32)(0x80 << 24)) {
        }
        magic[0] = 0x44; magic[1] = 0x52; magic[2] = 0x41; magic[3] = 0x43; magic[4] = 0x55;
        magic[5] = 0x4C; magic[6] = 0x41; magic[7] = 0x20; magic[8] = 0x41; magic[9] = 0x47; magic[10] = 0x42;
        sub_0801026C();
        for (block = 0; block < 8; block++)
            sub_08010320((u8)block);
    }
}
