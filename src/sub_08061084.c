extern u8 gCameraState[];
void spawnBudgetedEffect(void);

/* DMA-fill the 0xE0-byte palette block at 0x06001600 (bank chosen by bits
 * 2-3 of the control word) with the grey level byte at gCameraState+0x1439
 * replicated into both nibbles. */
s32 sub_08061084(void)
{
    u16 color;
    u16 *pColor = &color;
    u8 shade = gCameraState[0x1439];
    vu32 *dma;

    *pColor = shade | (shade << 4);

    dma = (vu32 *)0x040000D4;
    dma[0] = (u32)pColor;
    dma[1] = 0x06001600 + ((*(u16 *)(gCameraState + 0x1262) & 0xC) << 12);
    dma[2] = 0x810000E0;
    return dma[2];
}
