void sub_08010158(void);
void sub_080C3060(void *, s32, s32);
extern s32 D_02021E80;

/* Erase the current save block: fill a 16-byte stack buffer with zeros using a
 * fixed-source DMA3 fill, copy it over the SRAM block at the current save
 * address, then re-run the save-data setup/verification. */
void sub_08010214(void)
{
    s32 buf[4];
    s32 zero;
    s32 sramAddr;
    volatile u32 *dma;

    sramAddr = D_02021E80;
    zero = 0;
    dma = (volatile u32 *)0x040000D4;
    dma[0] = (u32)&zero;
    dma[1] = (u32)buf;
    dma[2] = 0x85000004;
    (void)dma[2];
    sub_080C3060(buf, sramAddr, 0x10);
    sub_08010158();
}
