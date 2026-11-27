extern volatile short D_0200E280;
extern vu32 D_0200E284;
extern vu16 gCrossfadeGfxState;
inline u32 dmaSrcBase()
{
  return (u32) 0x0200E290;
}

/* Stage the current graphics state into the work buffer at 0x02021E90, then
 * use DMA1 to push a palette block to VRAM and several tile/sprite blocks to
 * the object buffers around 0x0201E290. */
void sub_080064C4(void)
{
  u32 gfxSrc;
  u32 gfxDest;
  s32 dmaCtrl;
  vu32 *dma;
  u8 byteVal;
  u8 *bytePtr;
  gCrossfadeGfxState = D_0200E280;
  gfxSrc = 0x02021E90;
  *((vu32 *) (gfxSrc + 0x125C)) = D_0200E284;
  bytePtr = (u8 *)0x0200E288;
  byteVal = *bytePtr;
  *((vu8 *) (gfxSrc + (0x9B << 5))) = byteVal;
  dma = (vu32 *) 0x040000D4;
  dma[0] = dmaSrcBase();
  dma[1] = 0xC0 << 19;
  dma[2] = 0x80008000;
  (void) dma[2];
  gfxDest = (u32) 0x0201E290;
  dma[0] = gfxDest;
  dma[1] = gfxSrc + (0x93 << 5);
  dmaCtrl = 0x84000010;
  dma[2] = dmaCtrl;
  (void) dma[2];
  dma[0] = gfxDest + 0x40;
  dma[1] = gfxSrc + (0x95 << 5);
  dma[2] = dmaCtrl;
  (void) dma[2];
  dma[0] = gfxDest + 0x80;
  dma[1] = gfxSrc + ((0x95 << 5) + 0x40);
  dma[2] = dmaCtrl;
  (void) dma[2];
  gfxDest += 0xC0;
  dma[0] = gfxDest;
  dma[1] = gfxSrc + (0x99 << 5);
  dma[2] = dmaCtrl;
  (void) dma[2];
  dma[0] = (u32) 0x0201E390;
  dma[1] = gfxSrc + (0xA3 << 5);
  dma[2] = 0x84000003;
  (void) dma[2];
}
