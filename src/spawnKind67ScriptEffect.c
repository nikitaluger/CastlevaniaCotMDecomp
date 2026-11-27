struct GraphicsWorkspace { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GraphicsWorkspace gMainWorkspace;
struct EffectRenderPart { u8 _0, active, kind, layer; u16 gfxIndex, anim0, anim1, anim2, anim3, palette; u32 sprite; };
struct EffectWork { u8 _0[8]; u32 paramA, paramB; u8 _10[0xC]; s16 kind; u8 _1E[4]; s16 kindIndex; u8 _24[4]; struct EffectRenderPart *renderPart; };
struct EffectGfxEntry { u8 _0[0x04]; u16 gfxIndex; u16 palette; u8 _8[0x1E]; };
extern struct EffectGfxEntry gEffectGfxTable[];
extern u16 gScriptEffectAnimDefaults[];
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;
extern u32 gScriptEffectParams[];
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

/* Spawns a scripted kind-0x67 effect: allocates the actor and its work block,
 * fills in animation, graphics flags and palette from the shared tables and
 * script arguments, spawns its chained parts, then advances the script. On an
 * allocation failure the script's saved cleanup callback runs instead. */
void spawnKind67ScriptEffect(u8 *script) {
  s32 sprite;
  struct EffectWork *work;
  u8 *anim;
  u32 kindIndex;
  u8 *scriptPc;
  void **cmdTable;
  u8 *scriptState;
  u16 *animDefaults;

  sprite = (s32)allocSpriteObject();
  if (sprite == 0) goto fail;
  *(u32 *)(script + 0x38) = sprite;
  allocWorkSlot(script, 0, 0x48, 0);
  if (*(u32 *)(script + 0x3C) == 0) goto fail;
  *(u32 *)(sprite + 0x1C) = 2;
  work = (struct EffectWork *)*(u32 *)(script + 0x3C);
  anim = (u8 *)work + 0x34;
  installUpdateHandler(script, work, updateActorEffectSubObject);
  work->kind = 0x67;
  work->paramA = *(u32 *)(script + 0x5C);
  work->paramB = *(u32 *)(script + 0x6C);
  kindIndex = findKindIndex(0x67);
  work->kindIndex = kindIndex;
  if (((s16)kindIndex) < 0) goto fail;
  kindIndex = *(s16 *)((u8 *)work + 0x22);
  kindIndex = kindIndex << 6;
  kindIndex = kindIndex + 0x200;
  kindIndex &= 0xFC0;
  *(u16 *)sprite = kindIndex;
  *(u16 *)sprite |= gMainWorkspace.gfxFlags;
  initSpriteGraphics((void *)sprite, anim, (work->kind * 0xC) + (u32)gSpriteAnimDataTable);
  setAnimationFrame((void *)sprite, anim, 0x0C, 1);
  setSpriteFlipForDirection((void *)sprite, *(s32 *)(script + 0x7C));
  animDefaults = gScriptEffectAnimDefaults;
  work->renderPart = allocEffectPart();
  if (work->renderPart == NULL) goto fail;
  goto ok;
fail:
  sub_080C31E0(script, *(void **)(script + 0x24));
  return;
ok:
  work->renderPart->active = 5;
  work->renderPart->kind = 8;
  work->renderPart->layer = 1;
  work->renderPart->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
  work->renderPart->anim0 = animDefaults[0];
  work->renderPart->anim1 = animDefaults[1];
  work->renderPart->anim2 = animDefaults[2];
  work->renderPart->anim3 = animDefaults[3];
  work->renderPart->palette = gEffectGfxTable[work->kind].palette;
  work->renderPart->sprite = sprite;
  spawnChainedEffectObjects(script, 1, 5, *(u32 *)(sprite + 0x1C));
  *(u32 *)((u8 *)work + 0x10) = *(u32 *)(script + 0x7C) << 17;
  *(u32 *)((u8 *)work + 0x14) = gScriptEffectParams[*(u32 *)(script + 0x4C)];
  *(u16 *)(script + 2) |= 0x1000;
  {
    s16 idx = *(s16 *)(script + 0x22);
    *(u8 *)(script + (u32)idx * 2 + 0x19) = 0;
  }
  cmdTable = &gMainObjTimerCallbacks;
  scriptPc = script + 0x18;
  sub_080C31E4(scriptPc, script + 0x22, *cmdTable);
  {
    s16 idx = *(s16 *)(script + 0x22);
    *(u8 *)(script + (u32)idx * 2 + 0x19) += 1;
    idx = *(s16 *)(script + 0x22);
    scriptState = scriptPc + (u32)idx * 2;
    sub_080C31E0(script, *(void **)(*(u8 **)(script + 0x14) + *(u8 *)scriptState * 4));
  }
}
