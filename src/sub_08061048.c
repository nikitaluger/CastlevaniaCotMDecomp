extern u8 gCameraState[];

/* DMA-fill the palette area pointed to by game state +0x1450 with the grey
 * level byte at gCameraState+0x1439 replicated into both nibbles. */
void sub_08061048(void)
{
    u16 color;
    u16 *pColor = &color;
    u8 shade = gCameraState[0x1439];
    vu32 *dma;

    *pColor = shade | (shade << 4);

    dma = (vu32 *)0x040000D4;
    dma[0] = (u32)pColor;
    dma[1] = *(u32 *)(gCameraState + 0x1450);
    dma[2] = 0x810007E0;
    (void)dma[2];
}
