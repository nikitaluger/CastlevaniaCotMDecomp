extern struct FixedEffectWorkspace gMainWorkspace;
extern struct Kind44GfxEntry gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u16 gKind44EffectLayerAttrs[];
extern u32 gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);

/* Spawns the kind-0x44 effect: allocate the sprite and work state, set up their
 * animation and graphics from the shared tables, install one render layer, then
 * advance the parent's script step; allocation failures run the saved cleanup callback. */
void spawnKind44Effect(u8 *parent) {
  s32 sprite;
  struct FixedEffectState *work;
  u8 *animTrack;
  u32 kindIndex;
  u8 *slotArea;
  void **callbackTable;
  u8 *slot;
  u16 *layerAttrs;

  sprite = (s32)allocSpriteObject();
  if (sprite == 0) goto fail;
  *(u32 *)(parent + 0x38) = sprite;
  allocWorkSlot(parent, 0, 0x4C, 0);
  if (*(u32 *)(parent + 0x3C) == 0) goto fail;
  *(u32 *)(sprite + 0x1C) = 0x80000009;
  work = (struct FixedEffectState *)*(u32 *)(parent + 0x3C);
  animTrack = (u8 *)work + 0x34;
  installUpdateHandler(parent, work, updateActorEffectSubObject);
  work->kind = 0x44;
  work->worldX = *(u32 *)(parent + 0x4C);
  work->worldY = *(u32 *)(parent + 0x5C);
  kindIndex = findKindIndex(0x44);
  work->animSlot = kindIndex;
  if (((s16)kindIndex) < 0) goto fail;
  kindIndex = *(s16 *)((u8 *)work + 0x22);
  kindIndex = kindIndex << 6;
  kindIndex = kindIndex + 0x200;
  kindIndex &= 0xFC0;
  *(u16 *)sprite = kindIndex;
  *(u16 *)sprite |= gMainWorkspace.gfxFlags;
  *(u16 *)(sprite + 2) |= 0x400;
  initSpriteGraphics((void *)sprite, animTrack, (work->kind * 0xC) + (u32)gSpriteAnimDataTable);
  setAnimationFrame((void *)sprite, animTrack, 0x0C, 0);
  layerAttrs = gKind44EffectLayerAttrs;
  work->spriteLayer = allocEffectPart();
  if (work->spriteLayer == NULL) goto fail;
  goto ok;
fail:
  sub_080C31E0(parent, *(void **)(parent + 0x24));
  return;
ok:
  work->spriteLayer->active = 1;
  work->spriteLayer->param2 = 8;
  work->spriteLayer->param3 = 1;
  work->spriteLayer->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
  work->spriteLayer->anim0 = layerAttrs[0];
  work->spriteLayer->anim1 = layerAttrs[1];
  work->spriteLayer->anim2 = layerAttrs[2];
  work->spriteLayer->anim3 = layerAttrs[3];
  work->spriteLayer->palette = gEffectGfxTable[work->kind].palette;
  work->spriteLayer->object = sprite;
  *(u16 *)(parent + 2) |= 0x1000;
  {
    s16 stepIndex = *(s16 *)(parent + 0x22);
    *(u8 *)(parent + (u32)stepIndex * 2 + 0x19) = 0;
  }
  callbackTable = &gScriptStepCallbackTable;
  slotArea = parent + 0x18;
  sub_080C31E4(slotArea, parent + 0x22, *callbackTable);
  {
    s16 stepIndex = *(s16 *)(parent + 0x22);
    *(u8 *)(parent + (u32)stepIndex * 2 + 0x19) += 1;
    stepIndex = *(s16 *)(parent + 0x22);
    slot = slotArea + (u32)stepIndex * 2;
    sub_080C31E0(parent, *(void **)(*(u8 **)(parent + 0x14) + *(u8 *)slot * 4));
  }
}
