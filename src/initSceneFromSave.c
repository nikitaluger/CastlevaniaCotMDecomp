/* Sets up a scene: resets the background scroll registers and tilemap, DMA-loads the
 * graphics into VRAM, allocates the parent's two sub-objects when its target check
 * succeeds, runs a callback over the object list and advances the parent's script step. */
extern void postDisplaySprite(s32, void *, void *, s32, s32);
extern void *createChildObject(void *, s32);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void clearActorPool(void);
extern s32 sub_08006044(s32, s32, s32, s32, void *);
extern s32 decompressToVram(void *, void *);
extern s32 sub_080103F0(u8);
extern s32 sub_080C31E4(void *, void *, s32);
struct S_02025FF0 { u8 pad[8]; u8 b8; };
extern struct S_02025FF0 gMainWorkspace;
/* Initialises a scene: clears the camera's BG scroll/tilemap registers and the crossfade word, DMA-loads the four graphics blocks into VRAM, validates the selected save slot and creates the parent's two child objects when valid, then clears a menu word, walks the object list with a callback and advances the parent's script step. */ void initSceneFromSave(u8 *parent)
{
  u8 *camera;
  u8 *work;
  s32 saveValid;
  void *child0;
  u32 *callback;
  void *child1;
  s32 dmaMode;
  u16 *p;
  void *src, *dst;
  allocWorkSlot(parent, 0, 0x29C, 0);
  camera = (u8 *) 0x02021E90;
  *((u32 *) (camera + 0x125C)) = 0;
  *((u16 *) 0x03000830) = (*((u16 *) 0x03000830)) & 0xF0FF;
  {
    u16 *q = (u16 *) (camera + 0x1260);
    u32 mapBase = 0xD800;
    *q = mapBase;
    q = (u16 *) (0x99 << 5);
    p = (u16 *) (camera + (u32) q);
    *p = 0;
    q = (u16 *) ((u32) q - 0x40);
    p = (u16 *) (camera + (u32) q);
    *p = 0;
    q = (u16 *) ((u32) q - 0x40);
    p = (u16 *) (camera + (u32) q);
    *p = 0;
  }
  *((u16 *) (camera + 0x1262)) = 8;
  {
    u32 *scrollX = (u32 *) (camera + 0x1278);
    u32 *scrollY = (u32 *) (camera + 0x127C);
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
  dmaMode = 0x10;
  postDisplaySprite(1, src, dst, 0x60, dmaMode);
  src = (void *) 0x086399CC;
  dst = (void *) 0x050002C0;
  postDisplaySprite(1, src, dst, 0x20, dmaMode);
  work = *((u8 **) (parent + 0x3C));
  *((s32 *) (work + 0x0C)) = 0xA0;
  saveValid = sub_080103F0(gMainWorkspace.b8);
  *((s32 *) (work + 0x08)) = saveValid;
  if (saveValid != 0)
  {
    *((s32 *) (parent + 0x4C)) = -1;
    child0 = createChildObject(parent, 0x20);
    *((void **) (work + 0x00)) = child0;
    *((s32 *) (((u8 *) child0) + 0x4C)) = 0;
    child1 = createChildObject(parent, 0x20);
    *((void **) (work + 0x04)) = child1;
    *((s32 *) (((u8 *) child1) + 0x4C)) = 1;
  }
  *((u32 *) 0x020278D0) = 0;
  {
    void *func = (void *) 0x080C0385;
    sub_08006044(0, 5, 2, 0, func);
  }
  *((u8 *) ((parent + ((*((s16 *) (parent + 0x22))) * 2)) + 0x19)) = 0;
  callback = &(*((u32 *) 0x08671BB0));
  sub_080C31E4(parent + 0x18, parent + 0x22, *callback);
}
