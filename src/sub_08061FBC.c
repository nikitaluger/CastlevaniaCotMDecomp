extern void sub_080C2E68(void *, void *, s32);
extern void postDisplaySprite(void *, void *, void *, u32, u32);
extern void decompressToVram(void *, void *);
extern u8 gGameStatus[];

/* Reload the HUD/status-screen graphics: copy the 0x40-byte HUD record from
 * ROM 0x080DBDE0 into the work area at 0x02021E90, clear the two pending
 * bytes at gGameStatus+0x2DA/0x2DB, then upload the tiles and palettes selected
 * by the record's graphics word (bits 8-12 = tile base, bits 2-3 = palette
 * bank) to VRAM and palette RAM. DMA transfers use channel 3 at 0x040000D4;
 * each control write is read back because the hardware clears the enable bit. */
void sub_08061FBC(void)
{
  u16 fillWord;
  u32 ctrlSaved;
  u32 zero;
  vu32 *dmaCtrl;
  u8 *state = gGameStatus;
  u8 *hud = (u8 *) 0x02021E90;
  u8 *pendByte;
  vu32 *dma;
  u32 vramDest;

  sub_080C2E68(hud + (0x93 * 0x20), (void *) 0x080DBDE0, 0x40);
  pendByte = state + 0x2DA;
  zero = 0;
  *pendByte = zero;
  state[0x2DB] = zero;
  fillWord = zero;
  dma = (vu32 *) 0x040000D4;
  dma[0] = (u32) (&fillWord);
  dmaCtrl = &dma[2];
  dma[1] = 0x06008000;
  dma[2] = 0x81001000;
  (void) (*dmaCtrl);
  fillWord = zero;
  dma[0] = (u32) (&fillWord);
  hud += 0x1262;
  vramDest = 0x06000000 + (((0xF8 << 5) & (*((u16 *) hud))) << 3);
  dma[1] = vramDest;
  dma[2] = 0x81001000;
  (void) dma[2];
  postDisplaySprite((void *) 1, (void *) 0x08442374, (void *) vramDest, 0xC4, 0x10);
  decompressToVram((void *) 0x08441F60, (void *) (((0xC & (*((u16 *) hud))) << 12) + 0x06001800));
  dma[0] = (u32) 0x08442438;
  dma[1] = 0x05000020;
  dma[2] = 0x80000010;
  (void) (*dmaCtrl);
  dma[0] = (u32) 0x08442458;
  dma[1] = 0x05000040;
  dma[2] = 0x80000010;
  (void) dma[2];
  dma[0] = (u32) 0x08442478;
  dma[1] = 0x05000060;
  dma[2] = 0x80000010;
  (void) (*dmaCtrl);
  ctrlSaved = 0x80000010;
  decompressToVram((void *) 0x084424D8, (void *) (((0xC & (*((u16 *) hud))) << 12) + 0x06001000));
  dma[0] = (u32) 0x08442570;
  dma[1] = (((0xF8 << 5) & (*((u16 *) hud))) << 3) + 0x06000440;
  dma[2] = 0x80000060;
  (void) (*dmaCtrl);
  dma[0] = (u32) 0x08442630;
  dma[1] = 0x05000080;
  dma[2] = ctrlSaved;
  (void) dma[2];
}
