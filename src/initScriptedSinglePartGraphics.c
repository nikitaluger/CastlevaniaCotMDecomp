extern u16 gScriptedEffectLayerAttrs[];
extern u32 gScriptedEffectGfxDataA[];
extern u32 gScriptedEffectGfxDataB[];
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s16, s32);
extern void *allocEffectPart(void);
extern void installUpdateHandler(u8 *, u8 *, void *);
extern void sub_08014290(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
extern struct ScriptedEffectWorkspace gMainWorkspace;
extern struct ScriptedEffectScroll gCameraState;
extern struct ScriptedEffectKindEntry gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];

/* Build the single render layer of a scripted effect entity: allocate its
 * sprite and work state, pick a graphics id from its variant, start the
 * animation, place it against the camera scroll, then run the entry script's
 * first command and dispatch the resulting completion callback. */
void initScriptedSinglePartGraphics(struct ScriptedEffectEntity *entity)
{
  u32 gfxDataByVariant[4];
  int anim3Index;
  u32 highWord;
  u32 lowWord;
  u8 *sprite;
  struct ScriptedEffectWork *work;
  struct ScriptedEffectWork *workCheck;
  u8 *gfxInit;
  u8 *variantPtr;
  int deadOffset;
  u16 *layerAttrs;
  u8 *handlerTablePtr;
  s32 kindIndex;
  u32 spriteAttr;
  u32 zero;
  s16 frameId;
  s32 *timerCallback;
  u8 *workspace;
  u8 *unusedBase;
  u32 *animSrc;
  u32 animOffset;
  u8 variant;
  u8 *pt;
  u8 *pb;
  u8 *base1;
  u8 *base2;
  u32 idx;
  u8 opcode;
  highWord = gScriptedEffectGfxDataA[1];
  lowWord = gScriptedEffectGfxDataA[0];
  gfxDataByVariant[2] = lowWord;
  gfxDataByVariant[3] = highWord;
  highWord = gScriptedEffectGfxDataB[1];
  lowWord = gScriptedEffectGfxDataB[0];
  gfxDataByVariant[0] = lowWord;
  gfxDataByVariant[1] = highWord;
  sprite = allocSpriteObject();
  if (sprite == NULL)
  {
    goto fail;
  }
  entity->sprite = sprite;
  allocWorkSlot((u8 *) entity, 0, 0x48, 0);
  workCheck = *((struct ScriptedEffectWork * volatile *) (((u8 *) entity) + 0x3C));
  if (workCheck == NULL)
  {
    goto fail;
  }
  variantPtr = ((u8 *) entity) + 0x7C;
  *((u32 *) (((u8 *) sprite) + 0x1C)) = gfxDataByVariant[*((u8 *) variantPtr)];
  work = entity->work;
  gfxInit = ((u8 *) work) + 0x34;
  installUpdateHandler((u8 *) entity, (u8 *) work, (void *) sub_08014290);
  zero = 0;
  work->kind = SPRITE_KIND_SCRIPTED_SINGLE_PART;
  work->worldX = entity->worldX;
  work->worldY = entity->worldY;
  kindIndex = findKindIndex(SPRITE_KIND_SCRIPTED_SINGLE_PART);
  work->animSlot = kindIndex;
  if (((s32) (kindIndex << 16)) < 0)
  {
    goto fail;
  }
  spriteAttr = (((s32)work->animSlot) << 6) + 0x200;
  spriteAttr |= (kindIndex + 8) << 12;
  *((u16 *) sprite) = spriteAttr;
  workspace = (u8 *) (&gMainWorkspace);
  *((u16 *) sprite) = spriteAttr | (*((u16 *) (workspace + 0x18C2)));
  initSpriteGraphics(sprite, gfxInit, ((s32) gSpriteAnimDataTable) + (work->kind * 0xC));
  variant = *((u8 *) variantPtr);
  animOffset = variant * 4;
  animSrc = &gfxDataByVariant[2];
  frameId = *((s16 *) ((u32) animOffset + (u32) animSrc));
  setAnimationFrame(sprite, gfxInit, frameId, 0);
  layerAttrs = (u16 *) gScriptedEffectLayerAttrs;
  work->layer = (struct ScriptedEffectLayer *) allocEffectPart();
  if (work->layer != NULL)
  {
    goto main;
  }
  fail:
  _call_via_r1((u8 *) entity, *((s32 *) (((u8 *) entity) + 0x24)));
  goto end;
  deadOffset = 0x127C;
  main:
  work->layer->kind = RENDER_PART_KIND;
  work->layer->layer = zero;
  work->layer->priority = zero;
  work->layer->gfxIndex = gEffectGfxTable[work->kind].gfxIndex;
  work->layer->anim0 = layerAttrs[0];
  work->layer->anim1 = layerAttrs[1];
  work->layer->anim2 = layerAttrs[2];
  work->layer->anim3 = layerAttrs[anim3Index = 3];
  work->layer->palette = gEffectGfxTable[work->kind].palette;
  work->layer->object = (u32) sprite;
  entity->initialized = 1;
  {
    u8 *camera = (u8 *) &gCameraState;
    u8 *workspacePtr = (u8 *) &gMainWorkspace;
    u8 *scrollX;
    u8 *scrollY;
    u32 scrollIdx;
    workspacePtr += 0x18A8;
    scrollIdx = ((u32)*workspacePtr + 1) * 0x40;
    scrollX = camera + 0x1278;
    *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)work + 0x08) - ((*(u32 *)(scrollX + scrollIdx) + 0x8000) & 0xFFFF0000);
    scrollIdx = ((u32)*workspacePtr + 1) * 0x40;
    scrollY = camera + 0x127C;
    *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)work + 0x0C) - ((*(u32 *)(scrollY + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
  }
  entity->flags |= MULTI_PART_SPRITE_READY;
  *((u8 *) ((((u8 *) entity) + (2 * entity->scriptStep)) + 0x19)) = zero;
  timerCallback = (s32 *) MAIN_OBJ_TIMER_CALLBACK_TABLE;
  handlerTablePtr = ((u8 *) entity) + 0x14;
  variantPtr = ((u8 *) entity) + 0x18;
  highWord = 4;
  _call_via_r2(variantPtr, ((u8 *) entity) + 0x22, *timerCallback);
  *((u8 *) ((((u8 *) entity) + (2 * entity->scriptStep)) + 0x19)) += 1;
  variantPtr = variantPtr + (2 * entity->scriptStep);
  {
    u8 opcode = *((u8 *) variantPtr);
    _call_via_r1((u8 *) entity, *((u32 *) (*((u32 *) handlerTablePtr) + opcode * 4)));
  }
  end:
  ;
  ;
  ;
  ;
}
