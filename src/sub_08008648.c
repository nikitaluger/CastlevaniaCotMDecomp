/* Sets up a scene: resets the background scroll registers and tilemap, DMA-loads the
 * graphics into VRAM, allocates the parent's two sub-objects when its target check
 * succeeds, runs a callback over the object list and advances the parent's script step. */
extern void postDisplaySprite(s32, void *, void *, s32, s32);
extern void *sub_08001480(void *, s32);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void clearActorPool(void);
extern s32 sub_08006044(s32, s32, s32, s32, void *);
extern s32 decompressToVram(void *, void *);
extern s32 sub_080103F0(u8);
extern s32 sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 pad[8]; u8 b8; };
extern struct S_02025FF0 gMainWorkspace;
void sub_08008648(u8 *arg0)
{
  u8 *bgRegs;
  u8 *state;
  s32 targetFound;
  void *childA;
  u32 *callbackPtr;
  void *childB;
  s32 mode;
  u16 *p;
  void *src, *dst;
  allocWorkSlot(arg0, 0, 0x29C, 0);
  bgRegs = (u8 *) 0x02021E90;
  *((u32 *) (bgRegs + 0x125C)) = 0;
  *((u16 *) 0x03000830) = (*((u16 *) 0x03000830)) & 0xF0FF;
  {
    u16 *q = (u16 *) (bgRegs + 0x1260);
    u32 mapBase = 0xD800;
    *q = mapBase;
    q = (u16 *) (0x99 << 5);
    p = (u16 *) (bgRegs + (u32) q);
    *p = 0;
    q = (u16 *) ((u32) q - 0x40);
    p = (u16 *) (bgRegs + (u32) q);
    *p = 0;
    q = (u16 *) ((u32) q - 0x40);
    p = (u16 *) (bgRegs + (u32) q);
    *p = 0;
  }
  *((u16 *) (bgRegs + 0x1262)) = 8;
  {
    u32 *scrollX = (u32 *) (bgRegs + 0x1278);
    u32 *scrollY = (u32 *) (bgRegs + 0x127C);
    *scrollY = 0;
    *scrollX = 0;
  }
  clearActorPool();
  decompressToVram((void *) 0x086366CC, (void *) 0x0600A000);
  decompressToVram((void *) 0x08637DC8, (void *) 0x0600C000);
  decompressToVram((void *) 0x086395F8, (void *) 0x06010000);
  decompressToVram((void *) 0x086399EC, (void *) 0x06000000);
  src = (void *) 0x0863996C;
  dst = (void *) 0x05000100;
  mode = 0x10;
  postDisplaySprite(1, src, dst, 0x60, mode);
  src = (void *) 0x086399CC;
  dst = (void *) 0x050002C0;
  postDisplaySprite(1, src, dst, 0x20, mode);
  state = *((u8 **) (arg0 + 0x3C));
  *((s32 *) (state + 0x0C)) = 0xA0;
  targetFound = sub_080103F0(gMainWorkspace.b8);
  *((s32 *) (state + 0x08)) = targetFound;
  if (targetFound != 0)
  {
    *((s32 *) (arg0 + 0x4C)) = -1;
    childA = sub_08001480(arg0, 0x20);
    *((void **) (state + 0x00)) = childA;
    *((s32 *) (((u8 *) childA) + 0x4C)) = 0;
    childB = sub_08001480(arg0, 0x20);
    *((void **) (state + 0x04)) = childB;
    *((s32 *) (((u8 *) childB) + 0x4C)) = 1;
  }
  *((u32 *) 0x020278D0) = 0;
  {
    void *func = (void *) 0x080C0385;
    sub_08006044(0, 5, 2, 0, func);
  }
  *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = 0;
  callbackPtr = &(*((u32 *) 0x08671BB0));
  sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *callbackPtr);
}
