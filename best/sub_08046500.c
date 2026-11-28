extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, u32, u32, u32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s16);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(s32, void *, u16, u8);
extern void *allocEffectPart(void);
extern void setSpriteFlipForDirection(void *, s32);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08046A40(void);
extern u8 gMainWorkspace[];
extern u8 gCameraState[];
extern u32 gMainObjTimerCallbacks;

#define SETUP_LAYER(SLOT_PTR, OFF) do {                                          \
    u8 *layerAttrs = attrs + (OFF);                                             \
    *(u32 *)(SLOT_PTR) = (u32)allocEffectPart();                               \
    if (*(u32 *)(SLOT_PTR) == 0) goto fail;                                     \
    ((u8 *)*(u32 **)(SLOT_PTR))[1] = 0;                                         \
    ((u8 *)*(u32 **)(SLOT_PTR))[2] = 8;                                         \
    ((u8 *)*(u32 **)(SLOT_PTR))[3] = 1;                                         \
    *(u16 *)((u8 *)*(u32 **)(SLOT_PTR) + 4) = *(u16 *)(gfxAttrs + (*(s16 *)(work + 0x1C) * 40) + 4); \
    *(u16 *)((u8 *)*(u32 **)(SLOT_PTR) + 6) = *(u16 *)(layerAttrs);                   \
    *(u16 *)((u8 *)*(u32 **)(SLOT_PTR) + 8) = *(u16 *)(layerAttrs + 2);               \
    *(u16 *)((u8 *)*(u32 **)(SLOT_PTR) + 10) = *(u16 *)(layerAttrs + 4);              \
    *(u16 *)((u8 *)*(u32 **)(SLOT_PTR) + 12) = *(u16 *)(layerAttrs + 6);              \
    *(u16 *)((u8 *)*(u32 **)(SLOT_PTR) + 14) = *(u16 *)(gfxAttrs + (*(s16 *)(work + 0x1C) * 40) + 6); \
    *(u32 *)((u8 *)*(u32 **)(SLOT_PTR) + 0x10) = (u32)sprite;                         \
} while (0)

void sub_08046500(u8 *entity)
{
  u8 *sprite;
  u8 *work;
  u8 *animState;
  u8 *attrs;
  u8 *gfxAttrs;
  u32 spriteAttr;
  s32 slot;

  sprite = allocSpriteObject();
  if (sprite == 0)
    goto fail;
  *(u32 *)(entity + 0x38) = (u32)sprite;
  allocWorkSlot(entity, 0, 0x58, 0);
  if (*(u32 *)(entity + 0x3C) == 0)
    goto fail;
  *(u32 *)(sprite + 0x1C) = 0x08000009;
  work = *(u8 **)(entity + 0x3C);
  animState = 0x34 + work;
  installUpdateHandler(entity, work, (void *)sub_08046A40);
  *(u16 *)(work + 0x1C) = *(u16 *)(0x080CF84C + (entity[0x4C] * 4));
  *(u32 *)(work + 8) = *(u32 *)(entity + 0x5C);
  *(u32 *)(work + 0xC) = *(u32 *)(entity + 0x6C);
  *(u32 *)(work + 0x10) = ((s32)((s8)entity[0x7C]) * 3) << 15;
  slot = findKindIndex(*(s16 *)(work + 0x1C));
  *(u16 *)(work + 0x22) = slot;
  if ((slot << 16) < 0)
    goto fail;
  spriteAttr = (u32)(((s32)*(s16 *)(work + 0x22)) << 6) + (0x80 << 2);
  spriteAttr |= (slot + 8) << 12;
  spriteAttr |= *(u16 *)(gMainWorkspace + 0x18C2);
  *(u16 *)sprite = (u16)spriteAttr;
  initSpriteGraphics(sprite, animState, (void *)(0x080CD400 + (*(s16 *)(work + 0x1C) * 12)));
  setAnimationFrame((s32)sprite, animState, 13, 0);
  setSpriteFlipForDirection(sprite, *(s32 *)(work + 0x10));
  attrs = (u8 *)0x080CF5F8;
  gfxAttrs = (u8 *)0x080CBDD0;
  SETUP_LAYER(work + 0x28, 0x0);
  SETUP_LAYER(work + 0x48, 0x68);
  SETUP_LAYER(work + 0x4C, 0xD0);
  SETUP_LAYER(work + 0x50, 0x138);
  SETUP_LAYER(work + 0x54, 0x1A0);
  {
    u8 *camera = gCameraState;
    u8 *scrollPtr = gMainWorkspace + 0x18A8;
    u32 scrollIndex = ((u32)*scrollPtr + 1) * 0x40;
    *(u32 *)(sprite + 0x14) = *(u32 *)(work + 8) - ((*(u32 *)(camera + 0x1278 + scrollIndex) + 0x8000) & 0xFFFF0000);
    *(u32 *)(sprite + 0x18) = *(u32 *)(work + 0xC) - ((*(u32 *)(camera + 0x127C + scrollIndex) + 0xFFFF8000) & 0xFFFF0000);
  }
  *(u16 *)(entity + 2) |= 0x1000;
  {
    s32 step;
    u8 cmd;
    step = *(s16 *)(entity + 0x22);
    *(u16 *)(entity + 0x22) = step + 1;
    *(u8 *)(entity + step * 2 + 0x19) += 1;
    sub_080C31E4(entity + 0x18, entity + 0x22, *(u32 *)gMainObjTimerCallbacks);
    step = *(s16 *)(entity + 0x22);
    *(u16 *)(entity + 0x22) = step - 1;
    cmd = *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19);
    sub_080C31E0(entity, *(u32 *)(*(u32 *)(entity + 0x14) + cmd * 4));
  }
  return;
fail:
  sub_080C31E0(entity, *(u32 *)(entity + 0x24));
}
