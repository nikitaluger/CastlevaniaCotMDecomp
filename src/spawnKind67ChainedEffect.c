/* gEffectGfxTable record here has a 0x26-byte stride: tile id at +0x0C, palette at +0x0E. */
struct Kind67ChainedGfxEntry { u8 _0[0xC]; u16 gfxIndex; u16 palette; u8 _8[0x16]; };
extern struct FixedEffectWorkspace gMainWorkspace;
extern struct Kind67ChainedGfxEntry gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u16 gKind67ChainedLayerAttrs[];
extern u32 gScriptStepCallbackTable;
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void setSpriteFlipForDirection(void *, s32);
extern void spawnChainedEffectObjects(void *, s32, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void updateActorEffectSubObject(void);

/* Spawns the kind-0x67 chained script effect: allocate the sprite and work block,
 * fill in animation and graphics from the shared tables, create the child objects
 * and advance the script. An allocation failure runs the saved cleanup callback. */
void spawnKind67ChainedEffect(u8 *script) {
  s32 sprite;
  struct FixedEffectState *work;
  u8 *anim;
  u32 kindIndex;
  u8 *scriptStream;
  u32 *callbackTable;
  u8 *scriptStep;
  u16 *layerAttrs;

  sprite = (s32)allocSpriteObject();
  if (sprite == 0) goto fail;
  *(u32 *)(script + 0x38) = sprite;
  allocWorkSlot(script, 0, 0x48, 0);
  if (*(u32 *)(script + 0x3C) == 0) goto fail;
  *(u32 *)(sprite + 0x1C) = 2;
  work = (struct FixedEffectState *)*(u32 *)(script + 0x3C);
  anim = (u8 *)work + 0x34;
  installUpdateHandler(script, work, updateActorEffectSubObject);
  work->kind = 0x67;
  work->worldX = *(u32 *)(script + 0x5C);
  work->worldY = *(u32 *)(script + 0x6C);
  kindIndex = findKindIndex(0x67);
  work->animSlot = kindIndex;
  if (((s16)kindIndex) < 0) goto fail;
  kindIndex = *(s16 *)((u8 *)work + 0x22);
  kindIndex = kindIndex << 6;
  kindIndex = kindIndex + 0x200;
  kindIndex &= 0xFC0;
  *(u16 *)sprite = kindIndex;
  *(u16 *)sprite |= gMainWorkspace.gfxFlags;
  initSpriteGraphics((void *)sprite, anim, (work->kind * 0xC) + (u32)gSpriteAnimDataTable);
  setAnimationFrame((void *)sprite, anim, 0x16, 1);
  setSpriteFlipForDirection((void *)sprite, *(s32 *)(script + 0x7C));
  layerAttrs = gKind67ChainedLayerAttrs;
  work->spriteLayer = allocEffectPart();
  if (work->spriteLayer == NULL) goto fail;
  goto ok;
fail:
  sub_080C31E0(script, *(void **)(script + 0x24));
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
  spawnChainedEffectObjects(script, 2, 4, *(u32 *)((u8 *)sprite + 0x1C));
  *(u16 *)(script + 2) |= EFFECT_SPRITE_READY;
  {
    s16 stepIndex = *(s16 *)(script + 0x22);
    *(u8 *)(script + (u32)stepIndex * 2 + 0x19) = 0;
  }
  callbackTable = &gScriptStepCallbackTable;
  scriptStream = script + 0x18;
  sub_080C31E4(scriptStream, script + 0x22, *callbackTable);
  {
    s16 stepIndex = *(s16 *)(script + 0x22);
    *(u8 *)(script + (u32)stepIndex * 2 + 0x19) += 1;
    stepIndex = *(s16 *)(script + 0x22);
    scriptStep = scriptStream + (u32)stepIndex * 2;
    sub_080C31E0(script, *(void **)(*(u8 **)(script + 0x14) + *(u8 *)scriptStep * 4));
  }
}
