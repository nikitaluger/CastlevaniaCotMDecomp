extern void copyBytes(void *, void *, s32);
extern void postDisplaySprite(void *, void *, void *, u32, u32);
extern void decompressToVram(void *, void *);
extern u8 gGameStatus[];

/* Reload the HUD/status-screen graphics: copy the 0x40-byte HUD record from
 * ROM 0x080DBDE0 into the work area at 0x02021E90, clear the two pending
 * bytes at gGameStatus+0x2DA/0x2DB, then upload the tiles and palettes selected
 * by the record's graphics word (bits 8-12 = tile base, bits 2-3 = palette
 * bank) to VRAM and palette RAM. DMA transfers use channel 3 at 0x040000D4;
 * each control write is read back because the hardware clears the enable bit. */
/* Reload the HUD/status graphics: copy the status record into the work area, clear the two pending bytes, then DMA the tiles and palettes selected by the record's graphics word into VRAM and palette RAM. */ void reloadStatusGraphics(void)
{
  u16 fillWord;
  u32 dmaControlWord;
  u32 zero;
  vu32 *dmaControl;
  u8 *gameStatus = gGameStatus;
  u8 *statusWork = (u8 *) 0x02021E90;
  u8 *pendingByte;
  vu32 *dma3;
  u32 vramDest;

  copyBytes(statusWork + (0x93 * 0x20), (void *) 0x080DBDE0, 0x40);
  pendingByte = gameStatus + 0x2DA;
  zero = 0;
  *pendingByte = zero;
  gameStatus[0x2DB] = zero;
  fillWord = zero;
  dma3 = (vu32 *) 0x040000D4;
  dma3[0] = (u32) (&fillWord);
  dmaControl = &dma3[2];
  dma3[1] = 0x06008000;
  dma3[2] = 0x81001000;
  (void) (*dmaControl);
  fillWord = zero;
  dma3[0] = (u32) (&fillWord);
  statusWork += 0x1262;
  vramDest = 0x06000000 + (((0xF8 << 5) & (*((u16 *) statusWork))) << 3);
  dma3[1] = vramDest;
  dma3[2] = 0x81001000;
  (void) dma3[2];
  postDisplaySprite((void *) 1, (void *) 0x08442374, (void *) vramDest, 0xC4, 0x10);
  decompressToVram((void *) 0x08441F60, (void *) (((0xC & (*((u16 *) statusWork))) << 12) + 0x06001800));
  dma3[0] = (u32) 0x08442438;
  dma3[1] = 0x05000020;
  dma3[2] = 0x80000010;
  (void) (*dmaControl);
  dma3[0] = (u32) 0x08442458;
  dma3[1] = 0x05000040;
  dma3[2] = 0x80000010;
  (void) dma3[2];
  dma3[0] = (u32) 0x08442478;
  dma3[1] = 0x05000060;
  dma3[2] = 0x80000010;
  (void) (*dmaControl);
  dmaControlWord = 0x80000010;
  decompressToVram((void *) 0x084424D8, (void *) (((0xC & (*((u16 *) statusWork))) << 12) + 0x06001000));
  dma3[0] = (u32) 0x08442570;
  dma3[1] = (((0xF8 << 5) & (*((u16 *) statusWork))) << 3) + 0x06000440;
  dma3[2] = 0x80000060;
  (void) (*dmaControl);
  dma3[0] = (u32) 0x08442630;
  dma3[1] = 0x05000080;
  dma3[2] = dmaControlWord;
  (void) dma3[2];
}
